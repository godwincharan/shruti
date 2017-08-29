/*
  ==============================================================================

    TrackHolderComponent.h
    Created: 20 Jun 2016 8:54:20pm
    Author:  Charan DSouza

  ==============================================================================
*/

#ifndef TRACKHOLDERCOMPONENT_H_INCLUDED
#define TRACKHOLDERCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class TrackComponent;
class TrackAudioSource;
class AudioBlender;

class TrackHolderComponent   : public Viewport, public AsyncUpdater{
public:
    //==============================================================================
    TrackHolderComponent();
    ~TrackHolderComponent();

    void resized() override;
    
    void handleAsyncUpdate()override;

    void createTrackForSource(const TrackAudioSource* pTrackAudioSource, const AudioBlender* pAudioBlender);
    void deleteTrackForSource(const TrackAudioSource* pTrackAudioSource, const AudioBlender* pAudioBlender);
    void UpdatePlayHead(const AudioBlender* pAudioBlender);
private:
    ScopedPointer<Component> _pTrackGroupComponent;
    ScopedPointer<DrawableRectangle> _pPlayHead;
    Rectangle<float> _position;
    Array<TrackComponent*> _arrayOfTracks;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackHolderComponent)
};

#endif  // TRACKHOLDERCOMPONENT_H_INCLUDED
