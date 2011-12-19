
/* PropertyList.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#ifndef PROPERTYLIST_H
#define PROPERTYLIST_H

#include "../properties/Property.h"

class PropertyList
{
private:
    BaseProperty mProperty;
    PropertyList *mNext;

public:
    ~PropertyList();
    PropertyList(BaseProperty property);
    PropertyList(BaseProperty property, PropertyList* list);

    BaseProperty GetProperty();
    PropertyList* GetNextProperty();
    
    //unnötig?
    void AddProperty(BaseProperty property);
    void RemoveProperty(string const& key);
};
#endif
