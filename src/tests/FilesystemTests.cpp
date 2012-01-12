
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

BOOST_AUTO_TEST_SUITE(FilesystemTests_Suite)

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

BOOST_AUTO_TEST_SUITE_END()
