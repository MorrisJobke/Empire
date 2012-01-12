
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
#include "../Filesystem.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(TemplateTestSuite)

/*============================= BASIC TESTS ================================*/

BOOST_AUTO_TEST_CASE(NothingToReplaceShouldReturnOriginalInput)
{
    SimpleTemplate* tmpl = new SimpleTemplate();

    string input = "Realität ist da,\nwo der Pizzamann herkommt.";
    string output;
    tmpl->ParseString(input, output);

    BOOST_CHECK(input == output);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(ReplaceVariablePlaceholder)
{
    SimpleTemplate* tmpl = new SimpleTemplate();

    string individual = "Pizzamann";
    string key = "individual";
    GenProperty property(individual, key);
    tmpl->AddProperty(&property);

    string input = "Realität ist da,\nwo der @individual herkommt.@shouldDisappear";
    string output;
    tmpl->ParseString(input, output);

    BOOST_CHECK(output == "Realität ist da,\nwo der Pizzamann herkommt.");

    input = "email@@example.tld";
    tmpl->ParseString(input, output);

    //std::cout << "output: " << output << endl;

    BOOST_CHECK(output == "email@example.tld");
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(TemplateReadFileTest)
{
    SimpleTemplate* tmpl = new SimpleTemplate();

    string individual = "Bill Gates";
    string key = "unimportantPerson";    
    GenProperty property(individual, key);
    tmpl->AddProperty(&property);
    string path = "testtemplate";

    string input = "\"640 Kilobyte ought to be enough for anybody.\"\n@unimportantPerson, 1981@nothingToSeeHere";
    
    Filesystem::FileWriteString(path, input);

    string output;
    tmpl->ParseFile(path, output);

    BOOST_CHECK(output == "\"640 Kilobyte ought to be enough for anybody.\"\nBill Gates, 1981");
    
    remove(path.c_str());
}

BOOST_AUTO_TEST_SUITE_END()
