
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
        repo.CreatePropertyClass("RechnungsSteller", "String");
        repo.CreatePropertyClass("RechnungsNehmer", "String");
        repo.CreatePropertyClass("MeineZahl", "Integer");
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

BOOST_AUTO_TEST_CASE(testRepoLoad)
{
    Fs::ChangeCwd("test_repo");
    Fs::CreateDirectory(".emp");

    GenProperty prop1(42, "prop1");
    GenProperty prop2(4.32, "prop2");
    GenProperty prop3("hallo", "prop3");

    prop1.WriteMetadata(".emp");
    prop2.WriteMetadata(".emp");
    prop3.WriteMetadata(".emp");

    Repository repo;


    //Fs::PrintDirEntries(".emp");
    
    repo.Load();

    list<GenProperty*> prop_list = repo.GetPropertyList();

    BOOST_CHECK(*(prop_list.front()) == prop1);
    prop_list.pop_front();
    BOOST_CHECK(*(prop_list.front()) == prop2);
    prop_list.pop_front();
    BOOST_CHECK(*(prop_list.front()) == prop3);


    remove(".emp/prop1");
    remove(".emp/prop2");
    remove(".emp/prop3");

    remove(".emp");

    Fs::ChangeCwd("..");

}

BOOST_AUTO_TEST_SUITE_END()
