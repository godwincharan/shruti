/*
  ==============================================================================

    TimelineComponent.cpp
    Created: 22 Jun 2016 9:51:23pm
    Author:  Charan DSouza

  ==============================================================================
*/

#include "TimelineComponent.h"
#include "TimeDisplayComponent.h"
#include "../AudioBlender/AudioBlender.h"
#include "Constants.h"

TimelineComponent::TimelineComponent(const AudioBlender* pAudioBlender ):_pAudioBlender(pAudioBlender){
    addAndMakeVisible(_pTimeDisplayComp = new TimeDisplayComponent(pAudioBlender));
}

TimelineComponent::~TimelineComponent(){
    _pTimeDisplayComp = nullptr;
}

void TimelineComponent::resized(){
    _pTimeDisplayComp->setBounds(TRACK_WAVE_OFFSET,0, getWidth() - TRACK_WAVE_OFFSET,getHeight());
}

void TimelineComponent::updateTimeLine(){
    _pTimeDisplayComp->refreshTimeline();
}