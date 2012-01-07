#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Property
#endif
#include <boost/test/unit_test.hpp>
#include "../properties/PropertyInteger.h"
#include "../Filesystem.h"

BOOST_AUTO_TEST_SUITE(PropertyTests_Suite)

BOOST_AUTO_TEST_CASE(testType)
{
    PropertyInteger* property = new PropertyInteger("key", 42);
    BOOST_CHECK(property->GetType() == "Integer");
}

BOOST_AUTO_TEST_CASE(testSaveMeta)
{
    PropertyInteger* property = new PropertyInteger("key", 42);
    property->SaveMeta();
    string path;
    //path = GetMainPath();
    path = path + "meta.txt";
    BOOST_CHECK(Filesystem::FileExists(path) == true);
}

BOOST_AUTO_TEST_SUITE_END()
