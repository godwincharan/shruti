#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This class implements the desktop window that contains an instance of
    our MainComponent class.
*/

class MainComponent;

class MainWindow    : public DocumentWindow, MenuBarModel
{
public:
    MainWindow (String name);
    virtual ~MainWindow();
   
    void closeButtonPressed() override;

    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected (int menuItemID,int topLevelMenuIndex) override;
    
private:
    ScopedPointer<MainComponent> _pMainComponent;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};