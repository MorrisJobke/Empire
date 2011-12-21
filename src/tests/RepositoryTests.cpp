
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
#include "../Repository.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(RepositoryTests_Suite)

BOOST_AUTO_TEST_CASE(testRepository)
{
    Repository rep;

    cout << "testing repo" << endl;

    BOOST_CHECK(rep.IsOnTheRun() == true);
}

BOOST_AUTO_TEST_SUITE_END()
