/*
  ==============================================================================

    ShrutiToolbarItemFactory.h
    Created: 20 Nov 2016 1:38:20pm
    Author:  Charan DSouza

  ==============================================================================
*/

#ifndef SHRUTITOOLBARITEMFACTORY_H_INCLUDED
#define SHRUTITOOLBARITEMFACTORY_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <map>
using namespace std;

class ShrutiToolbarItemFactory   : public ToolbarItemFactory{
public:
    ShrutiToolbarItemFactory();
    ~ShrutiToolbarItemFactory();
    
    void 	                    getAllToolbarItemIds (Array< int > &ids) override;
    void 	                    getDefaultItemSet (Array< int > &ids) override;
 	ToolbarItemComponent * 	    createItem (int itemId) override;
private:
    Array<int> _itemIds;
    std::map<int,String> _itemIdToNameMap;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShrutiToolbarItemFactory)
};


#endif  // SHRUTITOOLBARITEMFACTORY_H_INCLUDED
