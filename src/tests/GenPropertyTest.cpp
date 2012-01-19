
/* GenPropertyTest.cpp
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-07.
 * @Editor:      Vim
 */

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE GenProperty
#endif

#include <iostream>
#include <string>
#include <list>

#include <stdio.h>

#include <boost/test/unit_test.hpp>

#include "../GenProperty.h"
#include "../Filesystem.h"
#include "../FunctionType.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(GenPropertyTestSuite)

/*============================= BASIC TESTS ================================*/

BOOST_AUTO_TEST_CASE(GenPropertyIntTest)
{
    int data_int = 42;
    string key = "testproperty";

    GenProperty<int> myprop_int(data_int, key);

    int ret_int = myprop_int.GetValue();

    BOOST_CHECK(ret_int == data_int);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyFloatTest)
{
    float data_float = 3.14159265;
    string key = "testproperty";

    GenProperty<float> myprop_float(data_float, key);

    float ret_float = myprop_float.GetValue();

    BOOST_CHECK(ret_float == data_float);
    BOOST_CHECK_CLOSE(ret_float, 3.14159265, 0.00001);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyDoubleTest)
{
    double data_double = 3.14159265;
    string key = "testproperty";

    GenProperty<double> myprop_double(data_double, key);

    double ret_double = myprop_double.GetValue();

    BOOST_CHECK(ret_double == data_double);
    BOOST_CHECK_CLOSE(ret_double, 3.14159265, 0.00000001);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyStringTest)
{
    string data_string = "I'm a really cool string";
    string key = "testproperty";

    GenProperty<string> myprop_string(data_string, key);

    string ret_string = myprop_string.GetValue();

    BOOST_CHECK(ret_string == data_string);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyFunctionTest)
{
    string map = "return amount * price;";
    string reduce = "return lhs + rhs;";
    list<string> functions;
    functions.push_back(map);
    functions.push_back(reduce);
    FunctionType func(functions);
    string key = "testproperty";

    // GenProperty<FunctionType> myprop_func(func, key);

    // FunctionType ret_function = myprop_func.GetValue();

    // BOOST_CHECK(ret_function == func);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyCopyConstructorTest)
{
    string data_string = "This is a really useless string...";
    string key = "useless";

    GenProperty<string> test_string(data_string, key);
    GenProperty<string> copied_prop(test_string);
    BOOST_CHECK(test_string == copied_prop);

    GenProperty<int> test_int(123, key);
    GenProperty<int> copied_prop2(test_int);
    BOOST_CHECK(test_int == copied_prop2);

    GenProperty<float> test_float(3.14152089, key);
    GenProperty<float> copied_prop3(test_float);
    BOOST_CHECK(test_float == copied_prop3);

    // FunctionProperty data_function = {
    //     "return amount * price;",
    //     "return lhs + rhs;"
    // };
    // GenProperty test_function(data_function, key);
    // GenProperty copied_prop4(test_function);
    // BOOST_CHECK(test_function == copied_prop4);
}

/*======================== OPERATOR TESTS    ==============================*/

BOOST_AUTO_TEST_CASE(GenPropertyAssignmentOperatorTest)
{
    GenProperty<float> myprop_float(3.88884448, "test1");
    GenProperty<float> myprop_float2(7.99999999, "test2");
    GenProperty<int> myprop_int(1023,"test3");
    GenProperty<int> myprop_int2(1024,"test4");
    GenProperty<string> myprop_string("test!", "test5");
    GenProperty<string> myprop_string2("test2!", "test6");

    myprop_float = myprop_float2;
    BOOST_CHECK(myprop_float == myprop_float2);
    myprop_int = myprop_int2;
    BOOST_CHECK(myprop_int == myprop_int2);
    myprop_string = myprop_string2;
    BOOST_CHECK(myprop_string == myprop_string2);
}

BOOST_AUTO_TEST_SUITE_END()
