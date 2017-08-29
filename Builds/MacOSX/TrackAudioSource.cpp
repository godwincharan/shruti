//
//  TrackAudioSource.cpp
//  Shruti
//
//  Created by Charan DSouza on 20/06/16.
//
//

#include "TrackAudioSource.hpp"


TrackAudioSource::TrackAudioSource(AudioFormatReaderSource* pAudioReaderSource): currentSampleRate (0.0),
bufferSizeExpected (0),
_pAudioReaderSource(pAudioReaderSource){
}

TrackAudioSource::~TrackAudioSource(){
    _pAudioReaderSource = nullptr;
}

void TrackAudioSource::prepareToPlay (int samplesPerBlockExpected, double sampleRate){
    tempBuffer.setSize (2, samplesPerBlockExpected);
    
    const ScopedLock sl (lock);
    
    currentSampleRate = sampleRate;
    bufferSizeExpected = samplesPerBlockExpected;
    
    _pAudioReaderSource->prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void TrackAudioSource::releaseResources(){
    const ScopedLock sl (lock);
    _pAudioReaderSource->releaseResources();

    tempBuffer.setSize (2, 0);
    currentSampleRate = 0;
    bufferSizeExpected = 0;
}

void TrackAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& info){
    const ScopedLock sl (lock);
    
    info.clearActiveBufferRegion();
    _pAudioReaderSource->getNextAudioBlock (info);
}

void TrackAudioSource::setNextReadPosition (int64 newPosition){
    _pAudioReaderSource->setNextReadPosition(newPosition);
}

int64 TrackAudioSource::getNextReadPosition() const{
    return _pAudioReaderSource->getNextReadPosition();
}

int64 TrackAudioSource::getTotalLength() const{
    return _pAudioReaderSource->getNextReadPosition();
}

bool TrackAudioSource::isLooping() const{
    return _pAudioReaderSource->isLooping();
}

void TrackAudioSource::setLooping (bool shouldLoop){
    _pAudioReaderSource->setLooping(shouldLoop);
}