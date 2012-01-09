
/* Repository.cc<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-12-21.
 * @Editor:      Vim
 */

#include "Repository.h"

namespace Fs = Filesystem;


/*============================= STATICS   ==================================*/

/** this function checks if a repo is Existent
 */
bool Repository::IsExistent()
{
    bool repo_found = false;
    std::string parent = "..";
    std::string repo_name = REPO_NAME;


    while(true)
    {
        std::string cwd;

        Fs::PrintCwd();
        repo_found = Fs::DirectoryExists(repo_name);
        
        if (repo_found == true)
            return true;
        
        cwd = Fs::GetCwd();
        if (cwd == "/")
            return false;

        Fs::ChangeCwd(parent);
    }
}


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/** the constructor
 */
Repository::Repository()
{
    std::string repo_path = REPO_NAME;

    if (Fs::DirectoryExists(repo_path))
        throw RepoExistentError();


    /* create the repo directory */
    try
    {
        Fs::CreateDirectory(repo_path);
    }
    catch(Fs::CannotCreateDirError &exc)
    {
        throw CannotCreateRepoError();
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** the destructor
 */
Repository::~Repository()
{
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/

/** method to add a new property class
 *
 * thsi creates a new metafile in the .emp folder with key as name and type as
 * content
 * @param the key
 * @param the type
 */
void Repository::CreatePropertyClass(const std::string &key, const std::string &type)
{
}

/*============================= ACESS      =================================*/

bool Repository::IsOnTheRun()
{
    return true;
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
