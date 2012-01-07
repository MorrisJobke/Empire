
/* RepositoryTests.cpp<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-12-21.
 * @Editor:      Vim
 */


#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE PropertyInteger
#endif

#include <iostream>
#include <string>

#include <stdio.h>

#include <boost/test/unit_test.hpp>

#include "../Repository.h"
#include "../Filesystem.h"

using namespace std;
namespace Fs = Filesystem;

BOOST_AUTO_TEST_SUITE(RepositoryTests_Suite)

BOOST_AUTO_TEST_CASE(testRepositoryCreation)
{
    Repository rep;

    string dir_name = ".emp";

    BOOST_CHECK(Fs::DirectoryExists(dir_name));
    
    remove(dir_name.c_str());
}

BOOST_AUTO_TEST_SUITE_END()
