#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE PropertyFunction
#endif
#include <boost/test/unit_test.hpp>
#include "../properties/PropertyInteger.h"
#include "../properties/PropertyFunction.cc"

BOOST_AUTO_TEST_SUITE(PropertyFunctionLuaTests_Suite)

BOOST_AUTO_TEST_CASE(lua)
{
    PropertyInteger* property1 = new PropertyInteger("int1", 42);
    PropertyInteger* property2 = new PropertyInteger("int2", 1295);

    PropertyFunction* func = new PropertyFunction("test", "int1 * int2", "lhs + rhs");
    func->AddProperty(*property1);
    func->AddProperty(*property2);

    BOOST_CHECK(func->GetValue() == 1337);
}

BOOST_AUTO_TEST_SUITE_END()