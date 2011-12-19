
/* PropertyList.cc
 * @Author:      Morris Jobke (uu.kabum@gmail.com)
 * @License:     GPL
 * @Created:     2011-12-18.
 * @Editor:      Vim
 */

#include "PropertyList.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/
PropertyList::PropertyList(BaseProperty property){}
PropertyList::PropertyList(BaseProperty property, PropertyListStruct* list){}
PropertyList::~PropertyList(){}
/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/

bool PropertyList::AddProperty(BaseProperty property)
{
    // add new item at head of list
    PropertyListStruct *oldHead = mPropertyList;
    PropertyListStruct *newHead = new PropertyListStruct;
    newHead->mProperty = property;
    newHead->mNext = oldHead;
    mPropertyList = newHead;

    return true;
}
bool PropertyList::RemoveProperty(string const& key){}

/*============================= ACCESS     =================================*/
BaseProperty PropertyList::GetProperty(string const& key){}
/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
