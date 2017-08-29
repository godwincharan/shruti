/*
  ==============================================================================

    TimelineComponent.h
    Created: 22 Jun 2016 9:51:23pm
    Author:  Charan DSouza

  ==============================================================================
*/

#ifndef TIMELINECOMPONENT_H_INCLUDED
#define TIMELINECOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AudioBlender;
class TimeDisplayComponent;

class TimelineComponent   : public Component{
public:
    TimelineComponent( const AudioBlender* pAudioBlender);
    ~TimelineComponent();

    void resized() override;
    void updateTimeLine();
    
private:
    const AudioBlender* _pAudioBlender;
    ScopedPointer<TimeDisplayComponent> _pTimeDisplayComp;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimelineComponent)
};
#endif  // TIMELINECOMPONENT_H_INCLUDED