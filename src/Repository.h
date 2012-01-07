
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


DEFINE_FAST_EXCEPTION(CannotCreateRepoError,"Cannot create repository")
DEFINE_FAST_EXCEPTION(RepoExistentError,"A repository exists here")


/** class which manages the Repository
 */
class Repository
{
    private:
    
    public:
    Repository();
    ~Repository();
    
    bool IsOnTheRun();

    
    static bool Existent();
};



#endif
