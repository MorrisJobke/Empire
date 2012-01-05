
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
#include <boost/test/unit_test.hpp>
#include "../Filesystem.h"

using namespace std;

namespace Fs = Filesystem;

BOOST_AUTO_TEST_SUITE(FilesystemTests_Suite)

BOOST_AUTO_TEST_CASE(testFilesystem)
{
    cout << "testing Filesystem" << endl;
    
    Fs::PrintCwd();

}

BOOST_AUTO_TEST_SUITE_END()
