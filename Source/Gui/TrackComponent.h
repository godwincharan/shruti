/*
  ==============================================================================

    TrackComponent.h
    Created: 20 Jun 2016 9:00:42pm
    Author:  Charan DSouza

  ==============================================================================
*/

#ifndef TRACKCOMPONENT_H_INCLUDED
#define TRACKCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class TrackAudioSource;
class TrackWidgetsComponent;
class TrackWaveformComponent;
class AudioBlender;

class TrackComponent   : public Component{
public:
    TrackComponent(const TrackAudioSource* pTrackAudioSource, const AudioBlender* pAudioBlender);
    ~TrackComponent();

    void resized() override;
    bool isHolding( const TrackAudioSource* pTrackAudioSource) const;
private:
    const TrackAudioSource* _pTrackAudioSource;
    const AudioBlender* _pAudioBlender;
    ScopedPointer<TrackWidgetsComponent> _pTrackWidgetsComponent;
    ScopedPointer<TrackWaveformComponent> _pTrackWaveformComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackComponent)
};
#endif  // TRACKCOMPONENT_H_INCLUDED
