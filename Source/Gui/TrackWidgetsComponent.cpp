/*
  ==============================================================================

    TrackWidgetsComponent.cpp
    Created: 21 Jun 2016 12:36:10am
    Author:  Charan DSouza

  ==============================================================================
*/

#include "TrackWidgetsComponent.h"
#include "../AudioBlender/AudioBlender.h"
#include "../AudioBlender/TrackAudioSource.h"

TrackWidgetsComponent::TrackWidgetsComponent(const TrackAudioSource* pTrackAudioSource,const AudioBlender* pAudioBlender):
_pAudioBlender(pAudioBlender),
_pTrackAudioSource(pTrackAudioSource){
    addAndMakeVisible(_pMuteButton = new TextButton("M"));
    _pMuteButton->addListener(this);
    _pMuteButton->setColour(TextButton::buttonOnColourId, juce::Colours::red);
    
    addAndMakeVisible(_pSoloButton = new TextButton("S"));
    _pSoloButton->addListener(this);
    _pSoloButton->setColour(TextButton::buttonOnColourId, juce::Colours::green);
    
    addAndMakeVisible(_pDeleteButton = new ImageButton("Detele Track"));
    _pDeleteButton->setImages ( false, true , true ,
                               ImageFileFormat::loadFrom(BinaryData::delete_png, BinaryData::delete_pngSize), 1.0, juce::Colours::transparentBlack ,
                               ImageFileFormat::loadFrom(BinaryData::delete_png, BinaryData::delete_pngSize), 1.0, juce::Colours::transparentBlack ,
                               ImageFileFormat::loadFrom(BinaryData::delete_png, BinaryData::delete_pngSize), 1.0, juce::Colours::transparentBlack );
    _pDeleteButton->addListener(this);
}

TrackWidgetsComponent::~TrackWidgetsComponent(){
    _pMuteButton = nullptr;
    _pSoloButton = nullptr;
    _pDeleteButton = nullptr;
}

void TrackWidgetsComponent::paint (Graphics& g){
    g.fillAll(Colours::aqua);
}

void TrackWidgetsComponent::resized(){
    _pDeleteButton->setBounds(2,2,20,20);
    _pMuteButton->setBounds(getWidth() - 25 , 10,20,20);
    _pSoloButton->setBounds(getWidth() - 25 , _pMuteButton->getBottom() + 10 ,20,20);
}

void TrackWidgetsComponent::buttonClicked (Button* pButton){
    if ( pButton == _pMuteButton){
        _pMuteButton->setToggleState(!_pMuteButton->getToggleState(),NotificationType::dontSendNotification);
        const_cast<TrackAudioSource*>(_pTrackAudioSource)->setMute(_pMuteButton->getToggleState());
    }
    else if ( pButton == _pSoloButton){
        _pSoloButton->setToggleState(!_pSoloButton->getToggleState(),NotificationType::dontSendNotification);
        const_cast<AudioBlender*>(_pAudioBlender)->setSoloTrack(const_cast<TrackAudioSource*>(_pTrackAudioSource),_pSoloButton->getToggleState());
    }
    else if ( pButton == _pDeleteButton ){
        const_cast<AudioBlender*>(_pAudioBlender)->deleteTrack(const_cast<TrackAudioSource*>(_pTrackAudioSource));
    }
}