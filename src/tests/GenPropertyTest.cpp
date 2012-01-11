
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
#include "../Filesystem.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(GenPropertyTestSuite)

/*============================= BASIC TESTS ================================*/

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

/*============================= IO TESTS    ================================*/

BOOST_AUTO_TEST_CASE(GenPropertyIntIOTest)
{
    string dir = "test_propterty_data";
    if (Filesystem::DirectoryExists(dir) == false)
        Filesystem::CreateDirectory(dir);


    int data_in = 42;
    string key = "int_test_property";
    string path = ".";

    GenProperty myprop(data_in, key);

    myprop.WriteMetadata(path);
    myprop.WriteData(dir + "/" + path);

    
    GenProperty read_prop;

    read_prop.ReadMetadata(key);
    read_prop.ReadData(dir + "/" + key);

    BOOST_CHECK(read_prop == myprop);

    remove("int_test_property");
    remove("test_propterty_data/int_test_property");
    remove("test_propterty_data");
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyFloatIOTest)
{
    string dir = "test_propterty_data";
    if (Filesystem::DirectoryExists(dir) == false)
        Filesystem::CreateDirectory(dir);


    float data_in = 42.34;
    string key = "float_test_property";
    string path = ".";

    GenProperty myprop(data_in, key);

    myprop.WriteMetadata(path);
    myprop.WriteData(dir + "/" + path);

    
    GenProperty read_prop;

    read_prop.ReadMetadata(key);
    read_prop.ReadData(dir + "/" + key);

    double data;

    read_prop.GetValue(data);
    
    BOOST_CHECK_CLOSE(data, 42.34, 0.001);

    remove("float_test_property");
    remove("test_propterty_data/float_test_property");
    remove("test_propterty_data");

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyStringIOTest)
{
    string dir = "test_propterty_data";
    if (Filesystem::DirectoryExists(dir) == false)
        Filesystem::CreateDirectory(dir);


    string data_in = "supa dupa string";
    string key = "string_test_property";
    string path = ".";

    GenProperty myprop(data_in, key);

    myprop.WriteMetadata(path);
    myprop.WriteData(dir + "/" + path);

    
    GenProperty read_prop;

    read_prop.ReadMetadata(key);
    read_prop.ReadData(dir + "/" + key);

    BOOST_CHECK(read_prop == myprop);

    remove("string_test_property");
    remove("test_propterty_data/string_test_property");
    remove("test_propterty_data");

}

BOOST_AUTO_TEST_CASE(GenPropertyFunctionTest)
{
    FunctionProperty data_function = {
        "return amount * price;",
        "return lhs + rhs;"
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
