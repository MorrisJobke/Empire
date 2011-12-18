#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Collection
#endif
#include <boost/test/unit_test.hpp>
#include "../collections/Collection.h"
#include "../properties/PropertyInteger.h"
#include "../properties/PropertyFloat.h"

BOOST_AUTO_TEST_SUITE(CollectionTests_Suite)

BOOST_AUTO_TEST_CASE(test2)
{
    Collection* coll = new Collection("key");
    BOOST_CHECK(coll->GetKey() == "key");
    BOOST_CHECK(coll->GetPropertylist() == NULL);
}

BOOST_AUTO_TEST_CASE(test3)
{
    PropertyInteger property ("intkey", 42);
    PropertyFloat property2 ("floatkey", "i am a property", 3.14159265);
    coll = new Collection("key");
    coll->AddProperty(property);
    coll->AddProperty(property2);
    BOOST_CHECK(coll->GetKey() == "key");
    BOOST_CHECK(coll->GetPropertylist->prop == property);
    BOOST_CHECK(coll->GetPropertylist->next->prop == property2);
    BOOST_CHECK(coll->GetPropertylist->next->next == NULL);
}

BOOST_AUTO_TEST_CASE(test4)
{
    coll = new Collection("key");
    Collection* coll2 = new Collection("key");
    BOOST_CHECK(coll->GetError == 1);
}

BOOST_AUTO_TEST_CASE(test5)
{
    coll = new Collection("key");
    coll->AddProperty(property3);
    BOOST_CHECK(coll->GetError == 2);
}

BOOST_AUTO_TEST_CASE(test5)
{
    coll = new Collection("key");
    coll->AddProperty(property3);
    BOOST_CHECK(coll->GetError == 2);
}

BOOST_AUTO_TEST_CASE(test6)
{
    coll = new Collection("key");
    coll2 = new Collection("key2");
    struct Collectionlist* colllist = Collectionlist();
    BOOST_CHECK(colllist->coll == coll);
    BOOST_CHECK(colllist->next->coll == coll2);
    BOOST_CHECK(colllist->next->next == NULL);
    delete(coll2);
}

BOOST_AUTO_TEST_CASE(test8)
{
    coll = new Collection("key");
    colllist = Collectionlist("key");
    BOOST_CHECK(colllist->coll == coll);
    BOOST_CHECK(colllist->next == NULL);
}
BOOST_AUTO_TEST_SUITE_END()
