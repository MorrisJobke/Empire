
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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GenPropertyCopyConstructorTest)
{
    string data_string = "This is a really useless string...";
    string key = "useless";
    
    bool error = false;
    
    //Test 1:
    GenProperty test_string(data_string, key);
    GenProperty copied_prop(test_string);
    if (!(test_string == copied_prop))
    {
        error = true;
        std::cout << "[GenProperty->CopyConstructorTest] FAIL @ TEST1" << std::endl;   
    }
    //Test 2:
    GenProperty test_int(123, key);
    GenProperty copied_prop2(test_int);
    if (!(test_int == copied_prop2))
    {
        error = true;
        std::cout << "[GenProperty->CopyConstructorTest] FAIL @ TEST2"  << std::endl;
    }
    //Test 3:
    GenProperty test_float(3.14152089, key);
    GenProperty copied_prop3(test_float);
    if (!(test_float == copied_prop3))
    {
        error = true;
        std::cout << "[GenProperty->CopyConstructorTest] FAIL @ TEST3" << std::endl;
    }
    //Test 4:
    FunctionProperty data_function = {
        "return amount * price;",
        "return lhs + rhs;"
    };
    GenProperty test_function(data_function, key);
    GenProperty copied_prop4(test_function);
    if (!(test_function == copied_prop4))
    {
        error = true;
        std::cout << "[GenProperty->CopyConstructorTest] FAIL @ TEST4" << std::endl;
    }

    BOOST_CHECK(!error);
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

/*======================== OPERATOR TESTS    ==============================*/

BOOST_AUTO_TEST_CASE(GenPropertyAssignmentOperatorTest)
{
    GenProperty myprop_float(3.88884448, "test1");
    GenProperty myprop_float2(7.99999999, "test2");
    GenProperty myprop_int(1023,"test3");
    GenProperty myprop_string("test!", "test4");
    
    std::string error = "";

    //TEST 1:
    myprop_float = myprop_float2;
    if (!(myprop_float == myprop_float2))
        error = "[GenProperty->AssignmentOperator] FAIL @ TEST 1";
    //TEST 2:
    myprop_float = myprop_int;
    if (!(myprop_float == myprop_int))    
        error = "[GenProperty->AssignmentOperator] FAIL @ TEST 2";
    //TEST 3:
    myprop_int = myprop_string;
    if (!(myprop_int == myprop_string))    
        error = "[GenProperty->AssignmentOperator] FAIL @ TEST 3";
    //TEST 4:
    myprop_string = myprop_float;
    if (!(myprop_string == myprop_float))    
        error = "[GenProperty->AssignmentOperator] FAIL @ TEST 4";
    
    if (error.compare(""))
    {
        std::cout << error << std::endl;
        BOOST_CHECK(false);    
    }
    else
        BOOST_CHECK(true);
}




BOOST_AUTO_TEST_SUITE_END()
