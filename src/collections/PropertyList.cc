
/* PropertyList.cc
 * @Author:      Morris Jobke (uu.kabum@gmail.com)
 * @License:     GPL
 * @Created:     2011-12-18.
 * @Editor:      Vim
 */

#include "PropertyList.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/
PropertyList::PropertyList() {}
PropertyList::~PropertyList(){}
/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/

bool
PropertyList::PropertyExists(string const& key)
{
    std::map<string, string>::const_iterator it = mPropertyList.find(key);
    return it != mPropertyList.end();
}

template<class T> void 
PropertyList::AddProperty(Property<T> property)
{
    mPropertyList[property.GetKey()] = property.ToString();
}

void
PropertyList::RemoveProperty(string const& key)
{
    mPropertyList.erase(key);
}

/*============================= ACCESS     =================================*/

string
PropertyList::GetPropertyValue(string const& key)
{
    if (!PropertyExists(key))
        throw PropertyNotExistsInList();
    
    return mPropertyList[key];
}

/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
