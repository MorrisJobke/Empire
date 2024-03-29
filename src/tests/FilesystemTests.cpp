
/* RepositoryTests.cpp<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-12-21.
 * @Editor:      Vim
 */


#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Filesystem
#endif

#include <iostream>
#include <string>

#include <stdio.h>

#include <boost/test/unit_test.hpp>

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

            /* create test repo dir */
            this->mTestRepoDir = "test_filesystem";

            try
            {
                Fs::CreateDirectory(this->mTestRepoDir);
            }
            catch(Fs::CannotCreateDirError &exc)
            {
                BOOST_FAIL( "Cannot create testing dir for filesystem module!" );
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

BOOST_FIXTURE_TEST_SUITE(FilesystemTests_Suite, Fixture)

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testFilesystem)
{

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** test the creation of a DirectoryExists
 *
 * if it is created remove it */
BOOST_AUTO_TEST_CASE(testDirCreation)
{
    string dir_name = "test_dir";

    BOOST_CHECK(Fs::DirectoryExists(dir_name) == false);

    if (Fs::DirectoryExists(dir_name) == false)
    {
        try
        {
            Fs::CreateDirectory(dir_name);
        }
        catch(Fs::CannotCreateDirError &exc)
        {
            cout << "Cannot create directory"  << endl;
            BOOST_CHECK(false);
        }

        remove(dir_name.c_str());
    }

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** test the creation of a file
 *
 * if it is created remove it */
BOOST_AUTO_TEST_CASE(testFileCreation)
{
    string content = "This is my\n Content";
    string path = "test_file";

    Fs::FileWriteString(path, content);


    BOOST_CHECK(Fs::FileExists(path) == true);

    remove(path.c_str());

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** test the delete of a file
 *
 */
BOOST_AUTO_TEST_CASE(testFileDelete)
{
    string content = "This is my\n Content";
    string path = "test_file";

    Fs::FileWriteString(path, content);


    BOOST_CHECK(Fs::FileExists(path) == true);

    Fs::FileDelete(path);

    BOOST_CHECK(Fs::FileExists(path) == false);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** test the reading of a file
 *
 * if it is created remove it */
BOOST_AUTO_TEST_CASE(testFileAppend)
{
    string content = "This is my\n Content";
    string path = "test_file";

    Fs::FileWriteString(path, content);

    string sec_content = "MORE CONTENT";

    Fs::FileAppendString(path, sec_content);

    BOOST_CHECK(Fs::FileExists(path) == true);

    remove(path.c_str());
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testWorkingDirOps)
{
    string str = "..";
    string old_cwd = Fs::GetCwd();

    Fs::ChangeCwd(str);

    Fs::ChangeCwd(old_cwd);

    BOOST_CHECK(old_cwd == Fs::GetCwd());
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(testDirLs)
{
    //Fs::PrintDirEntries("bin");
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

BOOST_AUTO_TEST_CASE(FileReadStringTest)
{
    string content = "This is my\n Content\n";
    string path = "test_file";

    Fs::FileWriteString(path, content);

    //std::cout << Fs::FileReadString(path) << std::endl;
    BOOST_CHECK(Fs::FileReadString(path).compare(content) == 0);

    remove(path.c_str());
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** test the recursive delete of directories
 *
 */
BOOST_AUTO_TEST_CASE(testRemoveDirRec)
{
    string dir_name = "test_dir2";

    try
    {
        Fs::CreateDirectory(dir_name);
    }
    catch(Fs::CannotCreateDirError &exc)
    {
        cout << "Cannot create directory"  << endl;
        BOOST_CHECK(false);
    }

    Fs::RemoveDirRec(dir_name);
    BOOST_CHECK(Fs::DirectoryExists(dir_name) == false);
}

BOOST_AUTO_TEST_CASE(testRemoveFilesInDirRec)
{
    string dir_name = "test_dir3";
    string dir2_name = "test_4";

    try
    {
        Fs::CreateDirectory(dir_name);
        Fs::FileWriteString(dir_name + "/" + "test1", "test");
        Fs::FileWriteString(dir_name + "/" + "test", "I'm a bad file.");
        Fs::CreateDirectory(dir2_name);
        Fs::FileWriteString(dir2_name + "/" + "test1", "test");
        Fs::FileWriteString(dir2_name + "/" + "test", "I'm a bad file.");
    }
    catch(Fs::CannotCreateDirError &exc)
    {
        cout << "Cannot create directory or file"  << endl;
        BOOST_CHECK(false);
    }

    Fs::RemoveFilesInDirRec("test", ".");

    BOOST_CHECK(Fs::FileExists(dir_name + "/" + "test1") == true);
    BOOST_CHECK(Fs::FileExists(dir_name + "/" + "test") == false);
    BOOST_CHECK(Fs::FileExists(dir2_name + "/" + "test1") == true);
    BOOST_CHECK(Fs::FileExists(dir2_name + "/" + "test") == false);

    Fs::RemoveDirRec(dir_name);
    Fs::RemoveDirRec(dir2_name);
}

BOOST_AUTO_TEST_SUITE_END()
