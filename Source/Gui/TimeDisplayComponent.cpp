/*
  ==============================================================================

    TimeDisplayComponent.cpp
    Created: 22 Jun 2016 10:05:39pm
    Author:  Charan DSouza

  ==============================================================================
*/

#include "TimeDisplayComponent.h"
#include "../AudioBlender/AudioBlender.h"

TimeDisplayComponent::TimeDisplayComponent(const AudioBlender* pAudioBlender ):_pAudioBlender(pAudioBlender){
}

TimeDisplayComponent::~TimeDisplayComponent(){
}

void TimeDisplayComponent::paint (Graphics& g){
    g.fillAll(Colours::darkgrey);
    g.setColour(Colours::white);
    int iWidth = getWidth();
    int64 iTotalDuration = _pAudioBlender->getTotalDuration();
    double dXIncr =  1000.0 * iWidth / iTotalDuration;
    double dX = 0;
    while( dX < iWidth){
        g.drawLine(dX,20,dX, 40);
        g.drawLine(dX + dXIncr/2,30,dX + dXIncr/2, 40);
        dX +=dXIncr;
    }
}

void TimeDisplayComponent::refreshTimeline(){
    repaint();
}