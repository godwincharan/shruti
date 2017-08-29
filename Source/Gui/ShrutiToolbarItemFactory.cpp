/*
  ==============================================================================

    ShrutiToolbarItemFactory.cpp
    Created: 20 Nov 2016 1:38:20pm
    Author:  Charan DSouza

  ==============================================================================
*/

#include "ShrutiToolbarItemFactory.h"
#include "../MainComponent.h"

ShrutiToolbarItemFactory::ShrutiToolbarItemFactory(){
    _itemIds.add(MainComponent::eAddTrack);
    _itemIdToNameMap[MainComponent::eAddTrack] = String("Add Track");
    
    _itemIds.add(MainComponent::ePlayPause);
    _itemIdToNameMap[MainComponent::ePlayPause] = String("Play/Pause");
}

ShrutiToolbarItemFactory::~ShrutiToolbarItemFactory(){
}
 
void ShrutiToolbarItemFactory::getAllToolbarItemIds (Array< int > &ids){
    ids.addArray(_itemIds);
}

void ShrutiToolbarItemFactory::getDefaultItemSet (Array< int > &ids){
    ids.addArray(_itemIds);
}

ToolbarItemComponent* ShrutiToolbarItemFactory::createItem (int itemId){
    Drawable* pNormalImage = nullptr;
    Drawable* pToggledOnImage = nullptr;
    switch (itemId){
        case MainComponent::eAddTrack:
            pNormalImage = Drawable::createFromImageData( BinaryData::addTrack_png , BinaryData::addTrack_pngSize);
            break;
        case MainComponent::ePlayPause:
            pNormalImage = Drawable::createFromImageData( BinaryData::play_png , BinaryData::play_pngSize);
            pToggledOnImage = Drawable::createFromImageData( BinaryData::pause_png , BinaryData::pause_pngSize);
            break;
    }
    
    ToolbarButton* pButton = nullptr;
    if ( pNormalImage){
        pButton = new ToolbarButton (itemId ,_itemIdToNameMap[itemId], pNormalImage, pToggledOnImage );
        pButton->setCommandToTrigger(&MainComponent::getApplicationCommandManager(),itemId, true);
    }
    
    return pButton;
}