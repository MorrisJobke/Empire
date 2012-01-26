
/* SyntaxParserTests.cpp
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-26.
 * @Editor:      Vim
 */

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE SyntaxParser
#endif

#include <iostream>
#include <string>
#include <list>

#include <stdio.h>
#include <pcre.h>

#include <boost/test/unit_test.hpp>

#include "../Repository.h"
#include "../Filesystem.h"
#include "../SyntaxParser.h"


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

BOOST_FIXTURE_TEST_SUITE(SynParTestSuite, Fixture)


BOOST_AUTO_TEST_CASE(CollAddAndFill)
{
    {
        char *iargs[] = { "lala", NULL };
        int iargsc = 1;

        /* init */
        SyntaxParser::init(iargsc, iargs);

        BOOST_CHECK(Fs::DirectoryExists(".emp") == true);
    }
    {
        /* add some props */
        char *iargs[] = { "stckzahl", "int", NULL };
        int iargsc = 2;
        SyntaxParser::create(iargsc, iargs);
    }
    {
        char *iargs[] = { "postenname", "string", NULL };
        int iargsc = 2;
        SyntaxParser::create(iargsc, iargs);
        BOOST_CHECK(Fs::FileExists(".emp/stckzahl") == true);
        BOOST_CHECK(Fs::FileExists(".emp/postenname") == true);
    }
    {
        /* add a collection */
        char *iargs[] = { "co", "stckzahl", "postenname", NULL };
        int iargsc = 3;
        SyntaxParser::coll_add(iargsc, iargs);
        BOOST_CHECK(Fs::DirectoryExists("co") == true);
        BOOST_CHECK(Fs::DirectoryExists("co/0") == true);
        BOOST_CHECK(Fs::FileExists("co/0/stckzahl") == true);
        BOOST_CHECK(Fs::FileExists("co/0/postenname") == true);
    }
    {
        /* fill collection */
        char *iargs[] = { "co", "stckzahl:43", "postenname:messer", NULL };
        int iargsc = 3;
        SyntaxParser::coll_fill(iargsc, iargs);
        BOOST_CHECK(Fs::DirectoryExists("co") == true);
        BOOST_CHECK_MESSAGE(Fs::DirectoryExists("co/1") == true, "Could not find collection entry 1");
        BOOST_CHECK(Fs::FileExists("co/1/stckzahl") == true);
        BOOST_CHECK(Fs::FileExists("co/1/postenname") == true);
    }
}



BOOST_AUTO_TEST_SUITE_END()
