
/* PropertyList.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#ifndef PROPERTYLIST_H
#define PROPERTYLIST_H

#include "../properties/Property.h"

struct PropertyListStruct
{
    BaseProperty mProperty;
    struct PropertyListStruct *mNext;
};

class PropertyList
{
private:
    struct PropertyListStruct *mPropertyList;

public:
    ~PropertyList();
    PropertyList(BaseProperty property);
    PropertyList(BaseProperty property, PropertyListStruct* list);

    bool AddProperty(BaseProperty property);
    bool RemoveProperty(string const& key);
    BaseProperty GetProperty(string const& key);
};
#endif
