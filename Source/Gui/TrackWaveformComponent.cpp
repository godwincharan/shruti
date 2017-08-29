/*
  ==============================================================================

    TrackWaveformComponent.cpp
    Created: 21 Jun 2016 12:44:23am
    Author:  Charan DSouza

  ==============================================================================
*/

#include "TrackWaveformComponent.h"
#include "../AudioBlender/TrackAudioSource.h"

TrackWaveformComponent::TrackWaveformComponent(const TrackAudioSource* pTrackAudioSource):_pTrackAudioSource(pTrackAudioSource){
}

void TrackWaveformComponent::paint (Graphics& g){
    g.fillAll( Colours::lightgrey);
    g.setColour(Colours::lightsalmon);
    _pTrackAudioSource->getAudioThumbnail()->drawChannels(g, getLocalBounds(), 0, _pTrackAudioSource->getAudioThumbnail()->getTotalLength(), 1);
}