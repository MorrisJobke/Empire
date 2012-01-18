
/* RepositoryTests.cpp
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-12-21.
 * @Editor:      Vim
 */


#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Repository
#endif

#include <iostream>
#include <string>
#include <list>

#include <stdio.h>

#include <boost/test/unit_test.hpp>

#include "../Repository.h"
#include "../Filesystem.h"

using namespace std;
namespace Fs = Filesystem;

BOOST_AUTO_TEST_SUITE(RepositoryTests_Suite)

BOOST_AUTO_TEST_CASE(testRepositoryCreation)
{
    /* if not existent create a folder for testing a repo */

    string repo_dir = "test_repo";

    if (Fs::DirectoryExists(repo_dir) == false)
        Fs::CreateDirectory(repo_dir);


    /* change dir, create repo and check */

    Fs::ChangeCwd(repo_dir);

    Repository repo;

    try
    {
        repo.Init();
    }
    catch(ExcRepository &exc)
    {
        cout << exc.what() << endl;
    }

    string meta_data_folder = ".emp";

    BOOST_CHECK(Fs::DirectoryExists(meta_data_folder));

    remove(meta_data_folder.c_str());

    /* change dir back */
    string parent = "..";
    Fs::ChangeCwd(parent);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(CreatePropertyFromTypeStringTest)
{
    Repository repo;

    GenPropertyBase* p_new_prop = repo.CreatePropertyFromTypeString("int");

    p_new_prop->SetKey("test_property");
    ((GenProperty<int>*) p_new_prop)->SetValue(42);

    // weiß der Geier warum, aber wenn diese Zeile auskommentiert ist, dann
    // gibt's nen memory access violation -.-
    // TODO
    cout << *p_new_prop << endl;

    //cout << "String representation: " << p_new_prop->ToString() << endl;

    delete p_new_prop;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testRepoCreateProperty)
{
    Fs::ChangeCwd("test_repo");

    Repository repo;

    try
    {
        repo.Init();
    }
    catch(ExcRepository &exc)
    {
        cout << exc.what() << endl;
    }

    try
    {
        repo.CreatePropertyClass("RechnungsSteller", "string");
        repo.CreatePropertyClass("RechnungsNehmer", "string");
        repo.CreatePropertyClass("MeineZahl", "int");
    }
    catch(ExcRepository &exc)
    {
        cout << exc.what() << endl;
    }

    BOOST_CHECK(Fs::FileExists(".emp/RechnungsSteller") == true);
    BOOST_CHECK(Fs::FileExists(".emp/RechnungsNehmer") == true);
    BOOST_CHECK(Fs::FileExists(".emp/MeineZahl") == true);

    remove(".emp/RechnungsSteller");
    remove(".emp/RechnungsNehmer");
    remove(".emp/MeineZahl");
    remove(".emp");

    Fs::ChangeCwd("..");

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(ReadMetaDataFromFile)
{
    Fs::ChangeCwd("test_repo");

    Repository repo;

    try
    {
        repo.Init();
    }
    catch(ExcRepository &exc)
    {
        cout << exc.what() << endl;
    }

    string in_type = "double";
    string in_key = "double_prop";


    try
    {
        repo.CreatePropertyClass(in_key, in_type);
    }
    catch(ExcRepository &exc)
    {
        cout << exc.what() << endl;
    }

    /* read meta data */
    string out_type = "";
    string out_key = "";

    PropertyIo::ReadMetaDataFromFile(".emp/double_prop", out_key, out_type);

    BOOST_CHECK(out_type == in_type);
    BOOST_CHECK(out_key == in_key);

    remove(".emp/double_prop");
    remove(".emp");

    Fs::ChangeCwd("..");
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testRepoPropDataIO)
{
    Fs::ChangeCwd("test_repo");

    Repository repo;

    try
    {
        repo.Init();
    }
    catch(ExcRepository &exc)
    {
        cout << exc.what() << endl;
    }


    GenProperty<int> out_prop(42, "out_prop");

    GenPropertyBase* p_out_prop = &out_prop;


    try
    {
        PropertyIo::WritePropDataToDir(".", p_out_prop);
    }
    catch(ExcRepository &exc)
    {
        cout << exc.what() << endl;
    }

    /* read data */
    GenProperty<int> in_prop("out_prop");

    GenPropertyBase* p_in_prop = &in_prop;

    PropertyIo::ReadDataFromFile("out_prop", p_in_prop);


    //cout << *p_out_prop << endl << *p_in_prop << endl;

    BOOST_CHECK(in_prop == out_prop);


    remove("out_prop");
    remove(".emp");

    Fs::ChangeCwd("..");
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testRepoLoad)
{

    /* create env */
    Fs::ChangeCwd("test_repo");

    Repository repo;

    try
    {
        repo.Init();
    }
    catch(ExcRepository &exc)
    {
        cout << exc.what() << endl;
    }


    GenProperty<string> rechst("ich_selbst", "rechsteller");
    GenProperty<string> firmn("firmen_name");

    GenPropertyBase* p_rechst = &rechst;

    repo.CreatePropertyClass(rechst.GetKey(), rechst.GetTypeN());
    repo.CreatePropertyClass(firmn.GetKey(), firmn.GetTypeN());

    PropertyIo::WritePropDataToDir(".", p_rechst);


    Fs::CreateDirectory("FirmaA");

    Fs::ChangeCwd("FirmaA");

    GenProperty<string> firmn_a("die Firma", "firmen_name");
    PropertyIo::WritePropDataToDir(".", &firmn_a);


    BOOST_CHECK(Fs::FileExists("firmen_name") == true);


    /* load repos */

    Repository repo_load;

    //Fs::PrintDirEntries(".emp");

    repo_load.Load();

    list<GenPropertyBase*> prop_list = repo_load.GetPropertyList();

    //cout << "comparing" << *(prop_list.front()) << " with " << firmn_a << endl;
    BOOST_CHECK(*((GenProperty<string>*) prop_list.front()) == firmn_a);
    prop_list.pop_front();
    //cout << "comparing " << *(prop_list.front()) << " with " << rechst << endl;
    BOOST_CHECK(*((GenProperty<string>*) prop_list.front()) == rechst);

    remove("firmen_name");
    Fs::ChangeCwd("..");
    remove("FirmaA");
    remove("rechsteller");

    remove(".emp/rechsteller");
    remove(".emp/firmen_name");

    remove(".emp");

    Fs::ChangeCwd("..");

}

BOOST_AUTO_TEST_SUITE_END()
