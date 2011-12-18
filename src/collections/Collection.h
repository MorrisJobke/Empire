
/* Collection.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include "Propertylist.h"
#ifndef PROPERTY_H
#   include "Property.cc"
#endif
using namespace std;

class Collection
{
private:
    string mKey;
    struct Propertylist *mPropertylist;

public:
    ~Collection();
    Collection(string const& key);
    Collection(string const& key, struct Propertylist *properties);

    string GetKey() const;
    void SetKey(string value);

    struct Propertylist *GetPropertylist() const;
    void SetPropertylist(struct Propertylist *properties);

    void AddProperty(BaseProperty property);
};
#endif
