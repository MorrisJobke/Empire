
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
    void AddProperty(BaseProperty property);
    void RemoveProperty(string const& key);
};
#endif
