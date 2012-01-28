
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

/* test fixture */
class Fixture
{
    public:
        std::string mBaseDir;
        std::string mTestRepoDir;

        Fixture()
        {
            BOOST_TEST_MESSAGE("Basedir:" << Fs::GetCwd());
            this->mBaseDir =  Fs::GetCwd();

            Fs::RemoveDirRec("test_repo");
            /* create test repo dir */
            this->mTestRepoDir = "test_repo";

            try
            {
                Fs::CreateDirectory(this->mTestRepoDir);
            }
            catch(Fs::CannotCreateDirError &exc)
            {
                BOOST_FAIL( "Cannot create testing repo dir!" );
            }

            /* change the dir path */
            Fs::ChangeCwd(this->mTestRepoDir);
        }

        ~Fixture()
        {
            BOOST_TEST_MESSAGE("Go back from:" << Fs::GetCwd());
            Fs::ChangeCwd(this->mBaseDir);

            /* delete repo dir */
            BOOST_TEST_MESSAGE("deleting test repo");
            Fs::RemoveDirRec(this->mTestRepoDir);

            BOOST_REQUIRE(Fs::DirectoryExists(this->mTestRepoDir) == false);

            if (Fs::DirectoryExists(this->mTestRepoDir) == false)
            {
                BOOST_TEST_MESSAGE("deleting test repo successfull");
            }

        }
};

BOOST_FIXTURE_TEST_SUITE(RepositoryTests_Suite, Fixture)


BOOST_AUTO_TEST_CASE(testRepositoryCreation)
{
    /* if not existent create a folder for testing a repo */

    /* create repo and check */
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

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(CreatePropertyFromTypeStringTest)
{
    Repository repo;

    GenPropertyBase* p_new_prop = PropertyHelpers::CreatePropertyFromTypeString("int");

    p_new_prop->SetKey("test_property");
    ((GenProperty<int>*) p_new_prop)->SetValue(42);

    BOOST_CHECK(p_new_prop->GetTypeN() == "int");

    delete p_new_prop;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testRepoCreateProperty)
{
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
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(ReadMetaDataFromFile)
{

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
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testRepoPropDataIO)
{

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
        PropertyIo::WriteDataToDir(".", p_out_prop);
    }
    catch(ExcRepository &exc)
    {
        cout << exc.what() << endl;
        BOOST_CHECK(false);
    }

    /* read data */
    GenProperty<int> in_prop("out_prop");

    GenPropertyBase* p_in_prop = &in_prop;

    PropertyIo::ReadDataFromFile("out_prop", p_in_prop);


    //cout << *p_out_prop << endl << *p_in_prop << endl;

    BOOST_CHECK(in_prop == out_prop);


    remove("out_prop");
    remove(".emp");

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testRepoLoad)
{


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

    PropertyIo::WriteDataToDir(".", p_rechst);


    Fs::CreateDirectory("FirmaA");

    Fs::ChangeCwd("FirmaA");

    GenProperty<string> firmn_a("die Firma", "firmen_name");
    PropertyIo::WriteDataToDir(".", &firmn_a);


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


}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testRepoRemovePropertyClass)
{

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

    repo.AddProperty("ich_selbst", "std::string", "Das ist ein String.");
    repo.AddProperty("intAuto", "", "123892");
    repo.AddProperty("floatAuto", "", "0.7863");
    repo.AddProperty("stringAuto", "", "Das ist keine Zahl...");

    BOOST_CHECK(repo.ContainsProperty("ich_selbst"));
    BOOST_CHECK(repo.ContainsProperty("intAuto"));
    BOOST_CHECK(repo.ContainsProperty("floatAuto"));
    BOOST_CHECK(repo.ContainsProperty("stringAuto"));

    remove(".emp/ich_selbst");
    remove(".emp/intAuto");
    remove(".emp/floatAuto");
    remove(".emp/stringAuto");
    remove(".emp");

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(GetFirstDefinedValueRecTest)
{

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

    repo.AddProperty("intAuto", "", "123892");
    repo.AddProperty("int2", "", "123");
    remove(".emp/intAuto");
    remove("intAuto");

    Fs::CreateDirectory("test");
    Fs::ChangeCwd("test");
    repo.AddProperty("intAuto", "", "892");

    std::string value = repo.GetPropertyValue("intAuto");
    BOOST_CHECK(value == "892");
    value = repo.GetPropertyValue("int2");
    BOOST_CHECK(value == "123");

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/* NOT NEEDED FOR NOW
BOOST_AUTO_TEST_CASE(AddPropertyStressTest)
{

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

    for (int i = 0; i < 100; i++)
    {
        repo.AddProperty("stressTest", "", "example");
        BOOST_CHECK(repo.ContainsProperty("stressTest"));
        remove(".emp/stressTest");
        remove("stressTest");
    }
}

BOOST_AUTO_TEST_SUITE_END()
*/
