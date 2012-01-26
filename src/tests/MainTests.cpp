#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include "../Filesystem.h"
#include "../DefineException.h"

namespace Fs = Filesystem;

BOOST_AUTO_TEST_SUITE(CleanUpSuite)

BOOST_AUTO_TEST_CASE(CleanUp)
{
//    if (Fs::DirectoryExists("test_repo") == true)
//        Fs::RemoveDirRec("test_repo");
//    BOOST_CHECK(Fs::FileExists("test_repo") == false);
//
//    if (Fs::DirectoryExists(".emp") == true)
//        Fs::RemoveDirRec(".emp");
//    BOOST_CHECK(Fs::FileExists(".emp") == false);
}

BOOST_AUTO_TEST_SUITE_END()
