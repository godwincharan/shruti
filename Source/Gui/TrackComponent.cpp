/*
  ==============================================================================

    TrackComponent.cpp
    Created: 20 Jun 2016 9:00:42pm
    Author:  Charan DSouza

  ==============================================================================
*/

#include "TrackComponent.h"
#include "../AudioBlender/TrackAudioSource.h"
#include "TrackWidgetsComponent.h"
#include "TrackWaveformComponent.h"
#include "../AudioBlender/AudioBlender.h"
#include "Constants.h"

TrackComponent::TrackComponent(const TrackAudioSource* pTrackAudioSource, const AudioBlender* pAudioBlender ):_pTrackAudioSource(pTrackAudioSource),
_pAudioBlender(pAudioBlender){
    addAndMakeVisible( _pTrackWidgetsComponent = new TrackWidgetsComponent(pTrackAudioSource,pAudioBlender));
    addAndMakeVisible(_pTrackWaveformComponent = new TrackWaveformComponent(pTrackAudioSource) );
}

TrackComponent::~TrackComponent(){
    _pTrackWidgetsComponent = nullptr;
    _pTrackWaveformComponent = nullptr;
}

void TrackComponent::resized(){
    _pTrackWidgetsComponent->setBounds(0,0,TRACK_WAVE_OFFSET,getHeight());
    int iAvailableWidth = getWidth() - TRACK_WAVE_OFFSET;
    int64 iTotalLength = _pAudioBlender->getTotalLength();
    int64 iCurTrackLength = _pTrackAudioSource->getTotalLength();
    int iWidth = iCurTrackLength * iAvailableWidth / iTotalLength;
    _pTrackWaveformComponent->setBounds(TRACK_WAVE_OFFSET,0,iWidth, getHeight());
}

bool TrackComponent::isHolding( const TrackAudioSource* pTrackAudioSource)const {
    return _pTrackAudioSource == pTrackAudioSource;
}