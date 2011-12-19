
/* PropertyList.cc
 * @Author:      Morris Jobke (uu.kabum@gmail.com)
 * @License:     GPL
 * @Created:     2011-12-18.
 * @Editor:      Vim
 */

#include "PropertyList.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

PropertyList::PropertyList(BaseProperty property)
{
    mProperty = property;
    mNext = NULL;
}

PropertyList::PropertyList(BaseProperty property, PropertyList* list)
{
    mProperty = property;
    mNext = list;
}

PropertyList::~PropertyList()
{
}
/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/
//unnötig?
void PropertyList::AddProperty(BaseProperty property)
{
}
//unnötig?
void PropertyList::RemoveProperty(string const& key)
{
}

/*============================= ACCESS     =================================*/

BaseProperty PropertyList::GetProperty()
{
return mProperty;
}

PropertyList* PropertyList::GetNextProperty()
{
return mNext;
}
/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
