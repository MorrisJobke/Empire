
/* PropertyList.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#ifndef PROPERTYLIST_H
#define PROPERTYLIST_H

#include <string>
#include <map>
#include <exception>

#include "../properties/Property.h"
#include "../DefineException.h"

class PropertyList
{
    /** exceptions
     */
    DEFINE_FAST_EXCEPTION(PropertyNotExistsInList, "Property does not exists in this list.")

private:
    struct std::map<string, string> mPropertyList;

public:
    ~PropertyList();
    PropertyList();

    bool PropertyExists(string const& key);
    template<class T> void AddProperty(Property<T> property);
    void RemoveProperty(string const& key);
    string GetPropertyValue(string const& key);
};
#endif
