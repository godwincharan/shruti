/*
  ==============================================================================

    TrackAudioSource.cpp
    Created: 20 Jun 2016 8:34:31pm
    Author:  Charan DSouza

  ==============================================================================
*/

#include "TrackAudioSource.h"
#include "AudioBlender.h"

TrackAudioSource::TrackAudioSource(const AudioBlender* pAudioBlender , AudioFormatReaderSource* pAudioReaderSource , AudioThumbnail* pThumbnail):
_pAudioBlender(pAudioBlender),
_pAudioReaderSource(pAudioReaderSource),
_pThumbnail(pThumbnail),
currentSampleRate (0.0),
bufferSizeExpected (0),
_bIsMute(false),
_bIsSolo(false){
    
}

TrackAudioSource::~TrackAudioSource(){
    _pAudioReaderSource = nullptr;
    _pThumbnail = nullptr;
}

void TrackAudioSource::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    tempBuffer.setSize (2, samplesPerBlockExpected);
    
    const ScopedLock sl (lock);
    
    currentSampleRate = sampleRate;
    bufferSizeExpected = samplesPerBlockExpected;
    
    _pAudioReaderSource->prepareToPlay (samplesPerBlockExpected, sampleRate);
    
    setNextReadPosition(_pAudioBlender->getNextReadPosition());
}

void TrackAudioSource::releaseResources()
{
    const ScopedLock sl (lock);
    
    _pAudioReaderSource->releaseResources();
    
    tempBuffer.setSize (2, 0);
    
    currentSampleRate = 0;
    bufferSizeExpected = 0;
}

void TrackAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& info){
    const ScopedLock sl (lock);
    
    info.clearActiveBufferRegion();
    int64 iNextReadPosition = getNextReadPosition();
    if ( _pAudioBlender->getNextReadPosition() == iNextReadPosition ){
        _pAudioReaderSource->getNextAudioBlock (info);
    }
    
    if ( _bIsMute){
        info.clearActiveBufferRegion();
    }
}

void TrackAudioSource::setNextReadPosition (int64 newPosition){
    _pAudioReaderSource->setNextReadPosition(newPosition);
}

int64 TrackAudioSource::getNextReadPosition() const{
    return _pAudioReaderSource->getNextReadPosition();
}

int64 TrackAudioSource::getTotalLength() const{
    return _pAudioReaderSource->getTotalLength();
}

bool TrackAudioSource::isLooping() const{
    return _pAudioReaderSource->isLooping();
}

void TrackAudioSource::setLooping (bool shouldLoop){
    _pAudioReaderSource->setLooping(shouldLoop);
}

bool TrackAudioSource::isMute() const{
    return _bIsMute;
}

void TrackAudioSource::setMute(bool shouldMute){
    _bIsMute = shouldMute;
}

bool TrackAudioSource::isSolo() const{
    return _bIsSolo;
}

void TrackAudioSource::setSolo(bool shouldSolo){
    _bIsSolo = shouldSolo;
}

AudioThumbnail* TrackAudioSource::getAudioThumbnail()const{
    return _pThumbnail;
}