
/* TemplateTests.cpp
 * @Author:      Brainafk
 * @License:     GPL
 * @Created:     2012-01-11.
 * @Editor:      Sublime Text 2
 */

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE PropertyInteger
#endif

#include <iostream>
#include <string>

#include <stdio.h>

#include <boost/test/unit_test.hpp>

#include "../Template.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(TemplateTestSuite)

/*============================= BASIC TESTS ================================*/

BOOST_AUTO_TEST_CASE(TEST_ME_BABY_ONE_MORE_TIME)
{
    BOOST_CHECK(true);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_SUITE_END()
