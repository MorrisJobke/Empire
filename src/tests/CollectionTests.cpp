
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
#include "../Repository.h"

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

        Repository working_repo;
        std::string meta_path = working_repo.GetMetaPath();

        mycol.Declare(prop_list, meta_path);
    }
    catch(ErrorColl &exc)
    {
        cout << exc.what() << endl;
    }

    BOOST_CHECK(Fs::DirectoryExists(".emp") == true);
    BOOST_CHECK(Fs::DirectoryExists(".emp/coll_test") == true);
    BOOST_CHECK(Fs::FileExists(".emp/coll_test/product") == true);
    BOOST_CHECK(Fs::FileExists(".emp/coll_test/units") == true);
    BOOST_CHECK(Fs::FileExists(".emp/coll_test/price") == true);

    remove(".emp/coll_test/product");
    remove(".emp/coll_test/units");
    remove(".emp/coll_test/price");
    remove(".emp/coll_test");
    remove(".emp");

}

BOOST_AUTO_TEST_CASE(CollectionAddRowTest)
{
    /* create some properties */

    GenProperty<string> product("product");
    GenProperty<string> unvalid("unvalid");
    GenProperty<int> units("units");
    GenProperty<double> price("price");

    std::list<GenPropertyBase*> prop_list;

    prop_list.push_back(&product);
    prop_list.push_back(&units);
    prop_list.push_back(&price);

    /* create entries */
    product.SetValue("Dildo");
    units.SetValue(4);
    price.SetValue(23.99);
    unvalid.SetValue("lolol");

    std::list<GenPropertyBase*> entry_list;
    entry_list.push_back(&product);
    entry_list.push_back(&units);
    entry_list.push_back(&price);
    entry_list.push_back(&unvalid);


    try
    {

        Coll mycol("coll_test");

        Repository working_repo;
        std::string meta_path = working_repo.GetMetaPath();

        mycol.Declare(prop_list, meta_path);

        mycol.AddRow(entry_list);
        mycol.AddRow(entry_list);
    }
    catch(ErrorColl &exc)
    {
        cout << exc.what() << endl;
    }





    BOOST_CHECK(Fs::DirectoryExists("coll_test") == true);
    BOOST_CHECK(Fs::DirectoryExists("coll_test/1") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/1/product") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/1/units") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/1/price") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/2/product") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/2/units") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/2/price") == true);

    remove(".emp/coll_test/product");
    remove(".emp/coll_test/units");
    remove(".emp/coll_test/price");
    remove(".emp/coll_test");
    remove(".emp");
    remove("coll_test/1/product");
    remove("coll_test/1/units");
    remove("coll_test/1/price");
    remove("coll_test/2/product");
    remove("coll_test/2/units");
    remove("coll_test/2/price");
    remove("coll_test/1");
    remove("coll_test/2");
    remove("coll_test");



}


BOOST_AUTO_TEST_CASE(CollectionPropTest)
{
    ///* create some properties */

    GenProperty<string> product("product");
    GenProperty<string> unvalid("unvalid");
    GenProperty<int> units("units");
    GenProperty<double> price("price");

    std::list<GenPropertyBase*> prop_list;

    prop_list.push_back(&product);
    prop_list.push_back(&units);
    prop_list.push_back(&price);

    /* create entries */
    product.SetValue("Dildo");
    units.SetValue(4);
    price.SetValue(23.99);
    unvalid.SetValue("lolol");

    std::list<GenPropertyBase*> entry_list;
    entry_list.push_back(&product);
    entry_list.push_back(&units);
    entry_list.push_back(&price);


    Repository working_repo;
    std::string meta_path = working_repo.GetMetaPath();
    try
    {

        Coll mycol("coll_test");

        mycol.Declare(prop_list, meta_path);

        mycol.AddRow(entry_list);
    }
    catch(ErrorColl &exc)
    {
        cout << exc.what() << endl;
    }





    BOOST_CHECK(Fs::DirectoryExists(".emp") == true);
    BOOST_CHECK(Fs::DirectoryExists(".emp/coll_test") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/1/product") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/1/units") == true);
    BOOST_CHECK(Fs::FileExists("coll_test/1/price") == true);



    /* try to load the collection */
    GenProperty<Coll> coll("collection");

    //Coll mycol = coll.GetValue();
    Coll mycol;

    try
    {
       mycol.Load("coll_test", meta_path);
       // mycol.DebugPrint();
    }
    catch(ErrorColl &exc)
    {
       cout << exc.what() << endl;
    }


    remove(".emp/coll_test/product");
    remove(".emp/coll_test/units");
    remove(".emp/coll_test/price");
    remove("coll_test/1/product");
    remove("coll_test/1/units");
    remove("coll_test/1/price");
    remove(".emp/coll_test");
    remove("coll_test/1");
    remove("coll_test");
    remove(".emp");

}

BOOST_AUTO_TEST_SUITE_END()
