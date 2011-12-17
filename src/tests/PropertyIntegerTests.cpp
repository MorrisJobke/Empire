#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PropertyInteger
#include <boost/test/unit_test.hpp>
#include <ctype.h>
#include "../properties/PropertyInteger.h"

BOOST_AUTO_TEST_CASE(typeIsInteger)
{
    BOOST_CHECK(42 == 42);
    PropertyInteger* property = new PropertyInteger(42);

    BOOST_CHECK(property->GetValue() == 42);
}

BOOST_AUTO_TEST_CASE(testOverloadedConstructors)
{
    PropertyInteger* property = new PropertyInteger(42);
    BOOST_CHECK(property->GetValue() == 42);
    BOOST_CHECK(property->GetKey() == "");
    BOOST_CHECK(property->GetDescription() == "");

    property = new PropertyInteger("key", 42);
    BOOST_CHECK(property->GetValue() == 42);
    BOOST_CHECK(property->GetKey() == "key");
    BOOST_CHECK(property->GetDescription() == "");

    property = new PropertyInteger("key", "i am a property", 42);
    BOOST_CHECK(property->GetValue() == 42);
    BOOST_CHECK(property->GetKey() == "key");
    BOOST_CHECK(property->GetDescription() == "i am a property");
}