/*
  ==============================================================================

    TrackWaveformComponent.h
    Created: 21 Jun 2016 12:44:23am
    Author:  Charan DSouza

  ==============================================================================
*/

#ifndef TRACKWAVEFORMCOMPONENT_H_INCLUDED
#define TRACKWAVEFORMCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class TrackAudioSource;

class TrackWaveformComponent   : public Component{
public:
    TrackWaveformComponent(const TrackAudioSource* pTrackAudioSource);
   
    void paint (Graphics& g) override;
    
private:
    const TrackAudioSource* _pTrackAudioSource;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackWaveformComponent)
};


#endif  // TRACKWAVEFORMCOMPONENT_H_INCLUDED
