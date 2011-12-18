
/* Collectionlist.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#ifndef COLLECTIONLIST_H
#define COLLECTIONLIST_H

#include "Collection.h"

struct Collectionlist
{
    Collection coll;
    struct Collectionlist *next;
};

#endif
