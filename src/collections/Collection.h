
/* <+FILE NAME+>
 * @Author:      <+AUTHOR+> (<+EMAIL+>)
 * @License:     <+LICENSE+>
 * @Created:     <+DATE+>.
 * @Editor:      Vim
 */

#ifndef COLLECTION_H
#define COLLECTION_H

#include <string>
#include "Propertylist.h"
using namespace std;

class Collection
{
private:
    string mKey;
    struct Propertylist *mPropertylist;
    void Init(string const& key);
    void Init(string const& key, struct Propertylist *properties);

public:
    Collection();
    ~Collection();

    string GetKey() const;
    void SetKey(string value);

    struct Propertylist *GetPropertylist() const;
    void SetPropertylist(struct Propertylist *properties);
};
#endif
