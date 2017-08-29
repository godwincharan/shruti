#include "MainWindow.h"
#include "MainComponent.h"

MainWindow::MainWindow (String name):
DocumentWindow (name,Colours::lightgrey,DocumentWindow::allButtons)
{
    setMenuBar(this);
    setUsingNativeTitleBar (true);
    setContentOwned (_pMainComponent = new MainComponent(), true);
    setResizable (true, true);

    centreWithSize (getWidth(), getHeight());
    setVisible (true);
}

MainWindow::~MainWindow(){
    
}

void MainWindow::closeButtonPressed(){
    setMenuBar(nullptr);
    // This is called when the user tries to close this window. Here, we'll just
    // ask the app to quit when this happens, but you can change this to do
    // whatever you need.
    JUCEApplication::getInstance()->systemRequestedQuit();
}

StringArray MainWindow::getMenuBarNames(){
    StringArray menuNames;
    menuNames.add(String("File"));
    return menuNames;
}

PopupMenu MainWindow::getMenuForIndex (int topLevelMenuIndex, const String& menuName){
    PopupMenu menu;
    menu.addItem(1, String("Add Track"));
    menu.addSeparator();
    menu.addItem(2, String("Play"));
    menu.addItem(3, String("Stop"));
    return menu;
}

void MainWindow::menuItemSelected (int menuItemID,int topLevelMenuIndex){
    if ( topLevelMenuIndex == 0){
        if ( menuItemID == 1){
            FileChooser chooser(String("Open audio file") ,
                                File::nonexistent,
                                String("*.mp3;*.ogg;*.wav;*.aiff;*.flac"));
            if ( chooser.browseForFileToOpen ()){
                _pMainComponent->addTrack(chooser.getResult());
            }
        }
        else if (menuItemID == 2 || menuItemID == 3){
            _pMainComponent->PlayStop();
        }
    }
}