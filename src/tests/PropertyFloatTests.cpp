#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE PropertyFloat
#endif
#include <boost/test/unit_test.hpp>
#include "../properties/PropertyFloat.h"

BOOST_AUTO_TEST_SUITE(PropertyFloatTests_Suite)

BOOST_AUTO_TEST_CASE(testOverloadedConstructors)
{
    PropertyFloat* property = new PropertyFloat("key", 3.14159265);
    BOOST_CHECK_CLOSE(property->GetValue(), 3.14159265, 0.00000001);
    BOOST_CHECK(property->GetKey() == "key");
    BOOST_CHECK(property->GetDescription() == "");

    property = new PropertyFloat("key", "i am a property", 3.14159265);
    BOOST_CHECK_CLOSE(property->GetValue(), 3.14159265, 0.00000001);
    BOOST_CHECK(property->GetKey() == "key");
    BOOST_CHECK(property->GetDescription() == "i am a property");
}

BOOST_AUTO_TEST_SUITE_END()