
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
#include "../properties/Property.h"

using namespace std;

class Collection
{
private:
    string mKey;
    PropertyList *mPropertylist;

public:
    ~Collection();
    Collection(string const& key);

    string GetKey() const;
    void SetKey(string value);

    void AddProperty(BaseProperty property);
    void RemoveProperty(BaseProperty property);
        
};
#endif
