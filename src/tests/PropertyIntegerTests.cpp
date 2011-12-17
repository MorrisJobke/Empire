#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE PropertyInteger
#endif
#include <boost/test/unit_test.hpp>
#include "../properties/PropertyInteger.h"

BOOST_AUTO_TEST_SUITE(PropertyIntegerTests_Suite)

BOOST_AUTO_TEST_CASE(testOverloadedConstructors)
{
    PropertyInteger* property = new PropertyInteger("key", 42);
    BOOST_CHECK(property->GetValue() == 42);
    BOOST_CHECK(property->GetKey() == "key");
    BOOST_CHECK(property->GetDescription() == "");

    property = new PropertyInteger("key", "i am a property", 42);
    BOOST_CHECK(property->GetValue() == 42);
    BOOST_CHECK(property->GetKey() == "key");
    BOOST_CHECK(property->GetDescription() == "i am a property");
}

BOOST_AUTO_TEST_SUITE_END()