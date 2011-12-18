#include "properties/PropertyInteger.h"
#include "collections/Collection.h"
#include "collections/Collectionlist.h"
#include <string>
#include <iostream>

struct Collectionlist *Collectionlist()
{
    Collectionlist* mCollectionlist = new Collectionlist;
    //fill Collectionlist with all Collections
    return mCollectionlist;
}


int main() {
    PropertyInteger intProp = PropertyInteger("test", 42);

    std::cout << "PropertyInteger: " << intProp.GetValue() << std::endl;

    return 0;
}
