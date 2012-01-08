
/* Repository.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-12-21.
 * @Editor:      Vim
 */

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>

#include "DefineException.h"
#include "Filesystem.h"

#define REPO_NAME ".emp"

DEFINE_FAST_EXCEPTION(CannotCreateRepoError,"Cannot create repository")
DEFINE_FAST_EXCEPTION(RepoExistentError,"A repository exists here")


/** class which manages the Repository
 */
class Repository
{
    private:
    std::string mRepoName;
    
    public:
    Repository();
    ~Repository();
    
    bool IsOnTheRun();

    
    static bool IsExistent();
};



#endif
