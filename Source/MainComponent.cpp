#include "MainComponent.h"
#include "Gui/TrackHolderComponent.h"
#include "Gui/TimelineComponent.h"
#include "Gui/ShrutiToolbarItemFactory.h"

ScopedPointer<ApplicationCommandManager> MainComponent::_pApplicationCommandManager = nullptr;

MainComponent::MainComponent():_audioBlender(*this){
    addAndMakeVisible(_pToolbar = new Toolbar());
    addAndMakeVisible(_pTimelineComponent = new TimelineComponent(&_audioBlender));
    addAndMakeVisible(_pTrackHolderComponent = new TrackHolderComponent());
    
    _pToolBarFactory = new ShrutiToolbarItemFactory();
    _pToolbar->addDefaultItems(*_pToolBarFactory);
    
    // this lets the command manager use keypresses that arrive in our window to send out commands
    addKeyListener (getApplicationCommandManager().getKeyMappings());
    setSize (800, 600);
}

MainComponent::~MainComponent(){
    _pTrackHolderComponent = nullptr;
    _pTimelineComponent = nullptr;
    _pToolBarFactory = nullptr;
    _pToolbar = nullptr;
    _pApplicationCommandManager = nullptr;
}

void MainComponent::paint (Graphics& g){
    g.fillAll (Colours::grey);
}

void MainComponent::resized(){
    int iY = 0;
    if ( _pToolbar){
        _pToolbar->setBounds(0,iY,getWidth(),30);
        iY += _pToolbar->getHeight();
    }
    
    if( _pTimelineComponent){
        _pTimelineComponent->setBounds(0,iY,getWidth(),40);
        iY += _pTimelineComponent->getHeight();
    }
    if ( _pTrackHolderComponent){
        _pTrackHolderComponent->setBounds(0,iY,getWidth(),getHeight());
        iY += _pTrackHolderComponent->getHeight();
    }
}

void MainComponent::TrackAdded(const TrackAudioSource* pTrackAudioSource){
    if ( _pTimelineComponent){
        _pTimelineComponent->updateTimeLine();
    }
    if ( _pTrackHolderComponent ){
        _pTrackHolderComponent->createTrackForSource(pTrackAudioSource, &_audioBlender);
    }
}

void MainComponent::TrackDeleted(const TrackAudioSource* pTrackAudioSource){
    if ( _pTimelineComponent){
        _pTimelineComponent->updateTimeLine();
    }
    if ( _pTrackHolderComponent ){
        _pTrackHolderComponent->deleteTrackForSource(pTrackAudioSource, &_audioBlender);
    }
}

void MainComponent::UpdatePosition(){
    if ( _pTrackHolderComponent ){
        _pTrackHolderComponent->UpdatePlayHead(&_audioBlender);
    }
}

void MainComponent::addTrack( const juce::File& audioFile ){
    _audioBlender.addTrack(audioFile);
}

void MainComponent::PlayStop(){
    _audioBlender.PlayStop();
}

ApplicationCommandManager& MainComponent::getApplicationCommandManager(){
    if (_pApplicationCommandManager == nullptr){
        _pApplicationCommandManager = new ApplicationCommandManager();
    }
    
    return *_pApplicationCommandManager;
}

ApplicationCommandTarget* MainComponent::getNextCommandTarget(){
    // this will return the next parent component that is an ApplicationCommandTarget (in this
    // case, there probably isn't one, but it's best to use this method in your own apps).
    return findFirstTargetParentComponent();
}

void MainComponent::getAllCommands (Array<CommandID>& commands){
    // this returns the set of all commands that this target can perform..
    const CommandID ids[] = { eAddTrack,
        ePlayPause
    };
    
    commands.addArray (ids, numElementsInArray (ids));
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result){
    const String sProjectCategory ("Project");
    
    switch (commandID){
        case eAddTrack:
            result.setInfo ("Add Track", "Add track to the project", sProjectCategory, 0);
            result.addDefaultKeypress ('+', ModifierKeys::commandModifier);
            break;
            
        case ePlayPause:
            result.setInfo ("Play/Pause", "Play and Pause the playback", sProjectCategory, _audioBlender.isPlaying()?ApplicationCommandInfo::isTicked:0);
            result.addDefaultKeypress ('p', ModifierKeys::commandModifier);
            break;
        default:
            break;
    }
}

bool MainComponent::perform (const InvocationInfo& info){
    switch (info.commandID){
        case eAddTrack:{
            FileChooser chooser(String("Open audio file") ,
                                File::nonexistent,
                                String("*.mp3;*.ogg;*.wav;*.aiff;*.flac"));
            if ( chooser.browseForFileToOpen ()){
                addTrack(chooser.getResult());
            }
        }
            break;
        case ePlayPause:{
            PlayStop();
        }
            break;
        default:
            return false;
    }
    
    return true;
}