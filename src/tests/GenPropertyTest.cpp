
/* GenPropertyTest.cpp
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-07.
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

#include "../GenProperty.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(GenPropertyTestSuite)

BOOST_AUTO_TEST_CASE(GenPropertyIntTest)
{
    int data_int = 42;
    string key = "testproperty";

    GenProperty myprop_int(data_int, key);

    int ret_int;
    myprop_int.GetValue(ret_int);

    BOOST_CHECK(ret_int == data_int);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyFloatTest)
{
    double data_float = 3.14159265;
    string key = "testproperty";

    GenProperty myprop_float(data_float, key);

    double ret_float;
    myprop_float.GetValue(ret_float);

    BOOST_CHECK(ret_float == data_float);
    BOOST_CHECK_CLOSE(ret_float, 3.14159265, 0.00000001);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyStringTest)
{
    string data_string = "I'm a really cool string";
    string key = "testproperty";

    GenProperty myprop_string(data_string, key);

    string ret_string;
    myprop_string.GetValue(ret_string);

    BOOST_CHECK(ret_string == data_string);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyWriteMetaDataTest)
{
    
    int data_int = 42;
    string key = "metadata_testfile";
    string path = ".";

    GenProperty myprop_int(data_int, key);

    myprop_int.WriteMetadata(path);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyWriteDataTest)
{
    
    int data_int = 42;
    string key = "data_testfile";
    string path = ".";

    GenProperty myprop_int(data_int, key);

    myprop_int.WriteData(path);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyFunctionTest)
{
    FunctionProperty data_function = {
        "amount * price",
        "lhs + rhs"
    };
    string key = "testproperty";

    GenProperty myprop_function(data_function, key);

    list<GenProperty> properties_1;
    list<GenProperty> properties_2;
    list< list<GenProperty> > properties;

    std::string price = "price";
    std::string amount = "amount";

    properties_1.push_back(*(new GenProperty(1.5, amount)));
    properties_1.push_back(*(new GenProperty(8, price)));

    properties_2.push_back(*(new GenProperty(2, amount)));
    properties_2.push_back(*(new GenProperty(15.0, price)));

    properties.push_back(properties_1);
    properties.push_back(properties_2);

    double ret_double;
    myprop_function.GetValue(ret_double, properties);

    BOOST_CHECK(ret_double == 42.0);
}

BOOST_AUTO_TEST_SUITE_END()
