
/* CollectionTests.cpp<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-19.
 * @Editor:      Vim
 */

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Collection
#endif

#include <iostream>
#include <string>
#include <list>

#include <stdio.h>

#include <boost/test/unit_test.hpp>

#include "../Collection.h"
#include "../Filesystem.h"

using namespace std;
namespace Fs = Filesystem;

BOOST_AUTO_TEST_SUITE(CollectionTests_Suite)

BOOST_AUTO_TEST_CASE(CollectionDeclareTest)
{
    /* create some properties */
    
    GenProperty<string> product("product"); 
    GenProperty<int> units("units"); 
    GenProperty<double> price("price"); 

    std::list<GenPropertyBase*> prop_list;

    prop_list.push_back(&product);
    prop_list.push_back(&units);
    prop_list.push_back(&price);

    try
    {

        Coll mycol("coll_test");

        mycol.Declare(prop_list);
    }
    catch(ErrorColl &exc)
    {
        cout << exc.what() << endl;
    }

    BOOST_CHECK(Fs::DirectoryExists("coll_test") == true);
    BOOST_CHECK(Fs::DirectoryExists("coll_test/0") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/0/product") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/0/units") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/0/price") == true);

    remove("coll_test/0/product");
    remove("coll_test/0/units");
    remove("coll_test/0/price");
    remove("coll_test/0");
    remove("coll_test");
    
}

BOOST_AUTO_TEST_SUITE_END()
