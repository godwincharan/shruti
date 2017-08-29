/*
  ==============================================================================

    TrackHolderComponent.cpp
    Created: 20 Jun 2016 8:54:20pm
    Author:  Charan DSouza

  ==============================================================================
*/

#include "TrackHolderComponent.h"
#include "TrackComponent.h"
#include "../AudioBlender/AudioBlender.h"
#include "Constants.h"

TrackHolderComponent::TrackHolderComponent(){
    setScrollBarsShown(true,false);
    setViewedComponent(_pTrackGroupComponent = new Component("TrackGroup"));
    _pTrackGroupComponent->addAndMakeVisible(_pPlayHead = new DrawableRectangle());
    _pPlayHead->setAlwaysOnTop(true);
    _pPlayHead->setFill(juce::Colours::red);
}

TrackHolderComponent::~TrackHolderComponent(){
    _pTrackGroupComponent = nullptr;
    _pPlayHead = nullptr;
    for( int i = 0 ; i < _arrayOfTracks.size();i++){
        delete _arrayOfTracks[i];
    }
    _arrayOfTracks.clear();
}
    
void TrackHolderComponent::resized(){
    const int iVisibleWidth =  getMaximumVisibleWidth();
    _pTrackGroupComponent->setBounds(0,0, iVisibleWidth, getHeight());
    int iY = 0;
    for( int i = 0 ; i < _arrayOfTracks.size();i++){
        _arrayOfTracks[i]->setBounds(0, iY, iVisibleWidth,TRACK_HEIGHT);
        iY += TRACK_HEIGHT;
    }
    _pTrackGroupComponent->setBounds(0,0, iVisibleWidth, iY);
    Viewport::resized();
}

void TrackHolderComponent::handleAsyncUpdate(){
    _pPlayHead->setRectangle(_position);
}

void TrackHolderComponent::createTrackForSource(const TrackAudioSource* pTrackAudioSource, const AudioBlender* pAudioBlender){
    TrackComponent* pTrackComponent = new TrackComponent(pTrackAudioSource,pAudioBlender);
    _pTrackGroupComponent->addAndMakeVisible(pTrackComponent);
    _arrayOfTracks.add(pTrackComponent);
    resized();
}

void TrackHolderComponent::deleteTrackForSource(const TrackAudioSource* pTrackAudioSource, const AudioBlender* pAudioBlender){
    TrackComponent* pTrackComponent = nullptr;
    for( int i = 0 ; i < _arrayOfTracks.size();i++){
        if ( _arrayOfTracks[i]->isHolding(pTrackAudioSource) ){
            pTrackComponent = _arrayOfTracks.removeAndReturn(i);
        }
    }
    if ( pTrackComponent ){
        deleteAndZero(pTrackComponent);
        resized();
    }
}

void TrackHolderComponent::UpdatePlayHead(const AudioBlender* pAudioBlender){
    const int iWaveformWidth =  getMaximumVisibleWidth() - TRACK_WAVE_OFFSET;
    int64 iTotalLenght = pAudioBlender->getTotalLength();
    int64 iCurrPos = pAudioBlender->getNextReadPosition();
    int iCurX = iCurrPos * iWaveformWidth / iTotalLenght +TRACK_WAVE_OFFSET;
    _position.setX(iCurX);
    _position.setY(0 );
    _position.setSize(2,getHeight());
    triggerAsyncUpdate();
}