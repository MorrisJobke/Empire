
/* Collection.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include "PropertyList.h"
#ifndef PROPERTY_CC
#   include "../properties/Property.cc"
#endif

using namespace std;

class Collection : public Property<PropertyList>
{
private:
    string mKey;
    PropertyList *mPropertyList;

public:
    ~Collection();
    Collection(string const& key);

    // void AddProperty(BaseProperty property);
    // void RemoveProperty(string const& key);
    // BaseProperty GetProperty(string const& key);
};
#endif
