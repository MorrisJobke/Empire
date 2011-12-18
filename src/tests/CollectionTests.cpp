#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Collection
#endif
#include <boost/test/unit_test.hpp>
#include "../collections/Collection.h"
#include "../properties/PropertyInteger.h"
#include "../properties/PropertyFloat.h"

BOOST_AUTO_TEST_SUITE(CollectionTests_Suite)

BOOST_AUTO_TEST_CASE(testOverloadedConstructors)
{
    Collection* coll = new Collection("key");
    BOOST_CHECK(coll->GetKey() == "key");
    BOOST_CHECK(coll->GetPropertylist() == NULL);

    coll = new Collection("key");
    PropertyInteger property ("intkey", 42);
    coll->AddProperty(property);
    PropertyFloat property2 ("floatkey", "i am a property", 3.14159265);
    coll->AddProperty(property2);
    BOOST_CHECK(coll->GetKey() == "key");
}

BOOST_AUTO_TEST_SUITE_END()
