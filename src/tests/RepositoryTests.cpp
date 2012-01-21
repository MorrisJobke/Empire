
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
#include <pcre.h> 

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
        string err = exc.what();
        if(err != "Err: Repo Exists")
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

    GenPropertyBase* p_new_prop = PropertyHelpers::CreatePropertyFromTypeString("int");

    p_new_prop->SetKey("test_property");
    ((GenProperty<int>*) p_new_prop)->SetValue(42);

    // cout << *p_new_prop << endl;

    // cout << "String representation: " << p_new_prop->ToString() << endl;

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
        string err = exc.what();
        if(err != "Err: Repo Exists")
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
        string err = exc.what();
        if(err != "Err: Repo Exists")
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
        string err = exc.what();
        if(err != "Err: Repo Exists")
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
        string err = exc.what();
        if(err != "Err: Repo Exists")
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
    GenProperty<string>* prop = (GenProperty<string>*) prop_list.front();
    BOOST_CHECK(*prop == firmn_a || *prop == rechst);
    prop_list.pop_front();
     prop = (GenProperty<string>*) prop_list.front();
    //cout << "comparing " << *(prop_list.front()) << " with " << rechst << endl;
    BOOST_CHECK(*prop == firmn_a || *prop == rechst);

    remove("firmen_name");
    Fs::ChangeCwd("..");
    remove("FirmaA");
    remove("rechsteller");

    remove(".emp/rechsteller");
    remove(".emp/firmen_name");

    remove(".emp");

    Fs::ChangeCwd("..");

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testRepoRemovePropertyClass)
{
    Fs::ChangeCwd("test_repo");

    Repository repo;

    try
    {
        repo.Init();
    }
    catch(ExcRepository &exc)
    {
        string err = exc.what();
        if(err != "Err: Repo Exists")
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
        string err = exc.what();
        if(err != "Err: Repo Exists")
            cout << exc.what() << endl;
    }

    BOOST_CHECK(Fs::FileExists(".emp/RechnungsSteller") == true);
    BOOST_CHECK(Fs::FileExists(".emp/RechnungsNehmer") == true);
    BOOST_CHECK(Fs::FileExists(".emp/MeineZahl") == true);

    repo.RemovePropertyClass("RechnungsSteller");
    repo.RemovePropertyClass("RechnungsNehmer");
    repo.RemovePropertyClass("MeineZahl");

    BOOST_CHECK(Fs::FileExists(".emp/RechnungsSteller") == false);
    BOOST_CHECK(Fs::FileExists(".emp/RechnungsNehmer") == false);
    BOOST_CHECK(Fs::FileExists(".emp/MeineZahl") == false);

    remove(".emp");
    
    Fs::ChangeCwd("..");

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/


BOOST_AUTO_TEST_CASE(testRegexMatch)
{
    char const* int_pattern = "^[+-]?\\d+$";
    char const* float_pattern = "^[+-]?((\\d+\\.\\d+)|\\.\\d+)$";

    /* should match: */
    BOOST_CHECK(RegexHelper::MatchesRegex("1234", int_pattern));
    BOOST_CHECK(RegexHelper::MatchesRegex("+1234", int_pattern));
    BOOST_CHECK(RegexHelper::MatchesRegex("-1234", int_pattern));

    BOOST_CHECK(RegexHelper::MatchesRegex("1234.4", float_pattern));
    BOOST_CHECK(RegexHelper::MatchesRegex("-.4", float_pattern));
    BOOST_CHECK(RegexHelper::MatchesRegex("+1234.4", float_pattern));

    /* shouldn't match: */
    BOOST_CHECK(!RegexHelper::MatchesRegex("1234.", int_pattern));
    BOOST_CHECK(!RegexHelper::MatchesRegex(".1234", int_pattern));
    BOOST_CHECK(!RegexHelper::MatchesRegex("s1234", int_pattern));
    BOOST_CHECK(!RegexHelper::MatchesRegex("1234s", int_pattern));
    BOOST_CHECK(!RegexHelper::MatchesRegex("Das ist eine Zahl: 1234", int_pattern));

    BOOST_CHECK(!RegexHelper::MatchesRegex("+12344", float_pattern));
    BOOST_CHECK(!RegexHelper::MatchesRegex("12.34.4", float_pattern));
    BOOST_CHECK(!RegexHelper::MatchesRegex("+12.34.4", float_pattern));
    BOOST_CHECK(!RegexHelper::MatchesRegex("+123.4s", float_pattern));
    BOOST_CHECK(!RegexHelper::MatchesRegex("1s234.4", float_pattern));
    BOOST_CHECK(!RegexHelper::MatchesRegex("s1234.4", float_pattern));

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(AddPropertyTest)
{
    /* create env */
    Fs::ChangeCwd("test_repo2");

    Repository repo;

    try
    {
        repo.Init();
    }
    catch(ExcRepository &exc)
    {
        string err = exc.what();
        if(err != "Err: Repo Exsists")
            cout << exc.what() << endl;
    }
    
    repo.AddProperty("ich_selbst", "std::string", "Das ist ein String.");
    repo.AddProperty("intAuto", "", "123892");
    repo.AddProperty("floatAuto", "", "0.7863");
    repo.AddProperty("stringAuto", "", "Das ist keine Zahl...");
    
    BOOST_CHECK(repo.ContainsProperty("ich_selbst"));
    BOOST_CHECK(repo.ContainsProperty("intAuto"));
    BOOST_CHECK(repo.ContainsProperty("floatAuto"));
    BOOST_CHECK(repo.ContainsProperty("stringAuto"));
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testRepoDeleteEnv)
{
    /** this test should always be the last one */
    if (Fs::DirectoryExists("test_repo") == true)
        remove("test_repo");
}

BOOST_AUTO_TEST_SUITE_END()
