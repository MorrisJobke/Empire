#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE PropertyFunction
#endif
#include <boost/test/unit_test.hpp>
#include "../properties/PropertyInteger.h"
#include "../properties/PropertyFunction.h"

BOOST_AUTO_TEST_SUITE(PropertyFunctionLuaTests_Suite)

BOOST_AUTO_TEST_CASE(lua)
{
    PropertyInteger* property1 = new PropertyInteger("int1", 42);
    PropertyInteger* property2 = new PropertyInteger("int2", 1295);

    PropertyFunction* mapReduceFunction = new PropertyFunction("test", "int1*int2", "a+b");

    BOOST_CHECK(function->GetValue() == 1337);
}

BOOST_AUTO_TEST_SUITE_END()