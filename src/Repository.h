
/* Repository.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-12-21.
 * @Editor:      Vim
 */

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>
#include <list>

#include "DefineException.h"
#include "Filesystem.h"
#include "GenProperty.h"

#define REPO_NAME ".emp"

DEFINE_FAST_EXCEPTION(CannotCreateRepoError,"Cannot create repository")
DEFINE_FAST_EXCEPTION(RepoExistentError,"A repository exists here")


/** class which manages the Repository
 */
class Repository
{
    private:
    std::string mRepoName;
    std::list<GenProperty*> PropertyList;

    
    public:
    Repository();
    ~Repository();
    
    bool IsOnTheRun();
    
    static bool IsExistent();
    static PropertyTypes GetPropTypeFromStr(std::string const& str);

    void CreatePropertyClass(std::string const& key, std::string const& type);
    void AddProperty(std::string const& key, std::string const& value);
    
    void RemoveProperty(std::string const& key);
    void RemovePropertyClass(std::string const& key);
    void RemovePropertyClassAndInstances(std::string const& key);
};



#endif
