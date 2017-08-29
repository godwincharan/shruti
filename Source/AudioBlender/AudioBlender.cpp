/*
  ==============================================================================

    AudioBlender.cpp
    Created: 17 Jun 2016 9:46:29pm
    Author:  Charan DSouza

  ==============================================================================
*/

#include "AudioBlender.h"
#include "TrackAudioSource.h"

AudioBlender::AudioBlender(AudioBlenderDelegate& delegate): currentSampleRate (0.0),
bufferSizeExpected (0),
_bShouldLoop(false),
_delegate(delegate),
_thumbnailCache(50),
_iNextReadPosition(0){
    _formatManager.registerBasicFormats();
    
    String audioError = _deviceManager.initialise (2, 2, nullptr, true);
    jassert (audioError.isEmpty());
    _deviceManager.addAudioCallback (&_audioSourcePlayer);
    _audioTransportSource.setSource(this);
    _audioSourcePlayer.setSource (&_audioTransportSource);
    setLooping(true);
}

AudioBlender::~AudioBlender(){
    if ( _audioTransportSource.isPlaying()){
        _audioTransportSource.stop();
    }
    
    _audioTransportSource.setSource(nullptr);
    _audioSourcePlayer.setSource (nullptr);
    _deviceManager.removeAudioCallback (&_audioSourcePlayer);
    _deviceManager.closeAudioDevice();
    
    removeAllInputs();
}

void AudioBlender::addTrack( const juce::File& audioFile ){
    AudioFormatReaderSource * pReaderSource = new AudioFormatReaderSource( _formatManager.createReaderFor(audioFile),true);
    pReaderSource->setLooping( isLooping());
    
    AudioThumbnail* pThumbnail = new AudioThumbnail(512,_formatManager,_thumbnailCache);
    pThumbnail->setSource( new FileInputSource(audioFile));
    
    TrackAudioSource* pTrackAudioSource = new TrackAudioSource(this,pReaderSource,pThumbnail);
    addInputSource(pTrackAudioSource, true);
    
    _delegate.TrackAdded(pTrackAudioSource);
    
    if ( _audioTransportSource.isPlaying()){
        _audioTransportSource.stop();
        _audioTransportSource.start();
    }
}

void AudioBlender::deleteTrack(TrackAudioSource* const pTrackAudioSource ){
    removeInputSource(pTrackAudioSource);
    _delegate.TrackDeleted(pTrackAudioSource);
}

void AudioBlender::PlayStop(){
    if ( _audioTransportSource.isPlaying()){
        _audioTransportSource.stop();
    }
    else{
        _audioTransportSource.start();
    }
}

//==============================================================================
void AudioBlender::addInputSource (TrackAudioSource* input, const bool deleteWhenRemoved)
{
    if (input != nullptr && ! inputs.contains (input))
    {
        double localRate;
        int localBufferSize;
        
        {
            const ScopedLock sl (lock);
            localRate = currentSampleRate;
            localBufferSize = bufferSizeExpected;
        }
        
        if (localRate > 0.0)
            input->prepareToPlay (localBufferSize, localRate);
        
        const ScopedLock sl (lock);
        
        inputsToDelete.setBit (inputs.size(), deleteWhenRemoved);
        inputs.add (input);
    }
}

void AudioBlender::removeInputSource (TrackAudioSource* const input)
{
    if (input != nullptr)
    {
        ScopedPointer<TrackAudioSource> toDelete;
        
        {
            const ScopedLock sl (lock);
            const int index = inputs.indexOf (input);
            
            if (index < 0)
                return;
            
            if (inputsToDelete [index])
                toDelete = input;
            
            inputsToDelete.shiftBits (-1, index);
            inputs.remove (index);
        }
        
        input->releaseResources();
    }
}

void AudioBlender::removeAllInputs()
{
    OwnedArray<TrackAudioSource> toDelete;
    
    {
        const ScopedLock sl (lock);
        
        for (int i = inputs.size(); --i >= 0;)
            if (inputsToDelete[i])
                toDelete.add (inputs.getUnchecked(i));
        
        inputs.clear();
    }
    
    for (int i = toDelete.size(); --i >= 0;)
        toDelete.getUnchecked(i)->releaseResources();
}

void AudioBlender::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    tempBuffer.setSize (2, samplesPerBlockExpected);
    
    const ScopedLock sl (lock);
    
    currentSampleRate = sampleRate;
    bufferSizeExpected = samplesPerBlockExpected;
    
    for (int i = inputs.size(); --i >= 0;)
        inputs.getUnchecked(i)->prepareToPlay (samplesPerBlockExpected, sampleRate);
    _iNextReadPosition = 0;
}

void AudioBlender::releaseResources()
{
    const ScopedLock sl (lock);
    
    for (int i = inputs.size(); --i >= 0;)
        inputs.getUnchecked(i)->releaseResources();
    
    tempBuffer.setSize (2, 0);
    
    currentSampleRate = 0;
    bufferSizeExpected = 0;
}

void AudioBlender::getNextAudioBlock (const AudioSourceChannelInfo& info){
    const ScopedLock sl (lock);
    
    info.clearActiveBufferRegion();
    
    const bool bHasSolo = HasSolo();

    tempBuffer.setSize (jmax (1, info.buffer->getNumChannels()),
                        info.buffer->getNumSamples());
    for (int i = 0; i < inputs.size(); ++i){
        int64 iSampleToRead = info.numSamples;
        int64 iNextReadPos = inputs.getUnchecked(i)->getNextReadPosition();
        int64 iTotalLength = inputs.getUnchecked(i)->getTotalLength();
        if( iNextReadPos + iSampleToRead > iTotalLength ){
            iSampleToRead = iTotalLength - iNextReadPos;
        }
        
        AudioSourceChannelInfo info2 (&tempBuffer, 0, iSampleToRead);
        inputs.getUnchecked(i)->getNextAudioBlock (info2);
        if ( bHasSolo ){
            if ( inputs.getUnchecked(i)->isSolo()){
                for (int chan = 0; chan < info.buffer->getNumChannels(); ++chan){
                    info.buffer->addFrom (chan, info.startSample, tempBuffer, chan, 0, iSampleToRead);
                }
            }
        }
        else{
            for (int chan = 0; chan < info.buffer->getNumChannels(); ++chan){
                info.buffer->addFrom (chan, info.startSample, tempBuffer, chan, 0, iSampleToRead);
            }
        }
    }
    
    if ( int64 iTotalLenght = getTotalLength()){
        _iNextReadPosition =  jmin(_iNextReadPosition+info.numSamples,iTotalLenght)%iTotalLenght;
        _delegate.UpdatePosition();
    }
}

void AudioBlender::setNextReadPosition (int64 newPosition){
    for (int i = inputs.size(); --i >= 0;){
        inputs.getUnchecked(i)->setNextReadPosition(newPosition);
    }
    _iNextReadPosition = newPosition;
}

int64 AudioBlender::getNextReadPosition() const{
//    int64 iNextReadPosition = 0;
//    for (int i = inputs.size(); --i >= 0;){
//        iNextReadPosition = jmax( inputs.getUnchecked(i)->getNextReadPosition(),iNextReadPosition);
//    }
    return _iNextReadPosition;
}

int64 AudioBlender::getTotalLength() const{
    int64 iTotalLength = 0;
    for (int i = inputs.size(); --i >= 0;){
        iTotalLength = jmax(inputs.getUnchecked(i)->getTotalLength(),iTotalLength);
    }
    return iTotalLength;
}

bool AudioBlender::isLooping() const{
    return _bShouldLoop;
}

void AudioBlender::setLooping (bool shouldLoop){
    _bShouldLoop = shouldLoop;
    for (int i = inputs.size(); --i >= 0;){
        inputs.getUnchecked(i)->setLooping(shouldLoop);
    }
}

void AudioBlender::setSoloTrack( TrackAudioSource* pTrackAudioSource, const bool shouldSolo){
    for (int i = inputs.size(); --i >= 0;){
        inputs.getUnchecked(i)->setSolo(false);
    }
    pTrackAudioSource->setSolo(shouldSolo);
}

bool AudioBlender::HasSolo() const{
    bool bHasSolo = false;
    for (int i = inputs.size(); --i >= 0;){
        bHasSolo |= inputs.getUnchecked(i)->isSolo();
    }
    return bHasSolo;
}

int64 AudioBlender::getTotalDuration() const{
    return getTotalLength()/currentSampleRate * 1000;
}

bool AudioBlender::isPlaying() const{
    return _audioTransportSource.isPlaying();
}