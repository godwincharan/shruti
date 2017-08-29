/*
  ==============================================================================

    TrackWidgetsComponent.h
    Created: 21 Jun 2016 12:36:10am
    Author:  Charan DSouza

  ==============================================================================
*/

#ifndef TRACKWIDGETSCOMPONENT_H_INCLUDED
#define TRACKWIDGETSCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AudioBlender;
class TrackAudioSource;

class TrackWidgetsComponent   : public Component, public Button::Listener{
public:
    TrackWidgetsComponent(const TrackAudioSource* pTrackAudioSource,const AudioBlender* pAudioBlender);
    ~TrackWidgetsComponent();
    
    void paint (Graphics& g) override;
    void resized() override;
    
    void buttonClicked (Button* pButton) override;
private:
    const AudioBlender* _pAudioBlender;
    const TrackAudioSource* _pTrackAudioSource;
    
    ScopedPointer<TextButton> _pMuteButton;
    ScopedPointer<TextButton> _pSoloButton;
    ScopedPointer<ImageButton> _pDeleteButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackWidgetsComponent)
};



#endif  // TRACKWIDGETSCOMPONENT_H_INCLUDED
