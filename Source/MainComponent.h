#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioBlender/AudioBlender.h"

class TrackHolderComponent;
class TimelineComponent;
class ShrutiToolbarItemFactory;

class MainComponent   : public Component, public AudioBlenderDelegate, public ApplicationCommandTarget
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();
    
    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
    void TrackAdded(const TrackAudioSource* pTrackAudioSource )override;
    void TrackDeleted(const TrackAudioSource* pTrackAudioSource) override;
    void UpdatePosition() override;
    
    void addTrack( const juce::File& audioFile );
    void PlayStop();
    
    // (return the command manager object used to dispatch command events)
    static ApplicationCommandManager& getApplicationCommandManager();
    
    enum CommandIDs{
        eAddTrack                    = 0x1000,
        ePlayPause                   = 0x1001,
    };
private:
    ApplicationCommandTarget* getNextCommandTarget() override;
    void getAllCommands (Array<CommandID>& commands) override;
    void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result) override;
    bool perform (const InvocationInfo& info) override;
private:
    AudioBlender _audioBlender;
    ScopedPointer<TrackHolderComponent> _pTrackHolderComponent;
    ScopedPointer<TimelineComponent> _pTimelineComponent;
    ScopedPointer<Toolbar>              _pToolbar;
    ScopedPointer<ShrutiToolbarItemFactory> _pToolBarFactory;
    
    static ScopedPointer<ApplicationCommandManager> _pApplicationCommandManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};