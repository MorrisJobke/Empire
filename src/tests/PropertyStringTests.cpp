#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE PropertyString
#endif
#include <boost/test/unit_test.hpp>
#include "../properties/PropertyString.h"

BOOST_AUTO_TEST_SUITE(PropertyStringTests_Suite)

BOOST_AUTO_TEST_CASE(testOverloadedConstructors)
{
    PropertyString* property = new PropertyString("key", "I'm a really cool string");
    BOOST_CHECK(property->GetValue() == "I'm a really cool string");
    BOOST_CHECK(property->GetKey() == "key");
    BOOST_CHECK(property->GetDescription() == "");

    property = new PropertyString("key", "i am a property", "I'm a really cool string");
    BOOST_CHECK(property->GetValue() == "I'm a really cool string");
    BOOST_CHECK(property->GetKey() == "key");
    BOOST_CHECK(property->GetDescription() == "i am a property");
}

BOOST_AUTO_TEST_SUITE_END()