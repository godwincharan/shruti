/*
  ==============================================================================

    TimeDisplayComponent.h
    Created: 22 Jun 2016 10:05:39pm
    Author:  Charan DSouza

  ==============================================================================
*/

#ifndef TIMEDISPLAYCOMPONENT_H_INCLUDED
#define TIMEDISPLAYCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AudioBlender;

class TimeDisplayComponent   : public Component{
public:
    TimeDisplayComponent( const AudioBlender* pAudioBlender);
    ~TimeDisplayComponent();
    
    void paint (Graphics& g) override;

    void refreshTimeline();
    
private:
    const AudioBlender* _pAudioBlender;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeDisplayComponent)
};

#endif  // TIMEDISPLAYCOMPONENT_H_INCLUDED
