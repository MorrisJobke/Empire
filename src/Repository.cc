
/* Repository.cc<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-12-21.
 * @Editor:      Vim
 */

#include "Repository.h"

namespace Fs = Filesystem;

/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/** the constructor
 */
Repository::Repository()
{
    std::string repo_path = ".emp";

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
/*============================= ACESS      =================================*/

bool Repository::IsOnTheRun()
{
    return true;
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
