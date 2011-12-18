#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Collection
#endif
#include <boost/test/unit_test.hpp>
#include "../collections/Collection.h"

BOOST_AUTO_TEST_SUITE(CollectionTests_Suite)

BOOST_AUTO_TEST_CASE(testOverloadedConstructors)
{
    Collection* coll = new Collection("key");
    BOOST_CHECK(coll->GetKey() == "key");
    BOOST_CHECK(coll->GetPropertylist() == NULL);

    PropertyInteger* property = new PropertyInteger("intkey", 42);
    PropertyFloat* property2 = new PropertyFloat("floatkey", "i am a property", 3.14159265);
    PropertyList* proplist = new Propertylist;
    proplist->prop = property;
    proplist->next = new Propertylist;
    proplist->next->prop = property2;
    proplist->next->next = NULL;    
    coll = new Collection("key", proplist);
    BOOST_CHECK(coll->GetKey() == "key");
    BOOST_CHECK(coll->GetPropertylist() == proplist);
}

BOOST_AUTO_TEST_SUITE_END()
