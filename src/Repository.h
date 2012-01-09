
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
    std::list<GenProperty> PropertyList;

    
    public:
    Repository();
    ~Repository();
    
    bool IsOnTheRun();
    
    static bool IsExistent();
    static PropertyTypes GetPropTypeFromStr(const std::string& str);

    void CreatePropertyClass(const std::string& key, const std::string& type);
    void AddProperty(const std::string& key, const std::string& value);
    
    void RemoveProperty(const std::string& key);
    void RemovePropertyClass(const std::string& key);
    void RemovePropertyClassAndInstances(const std::string& key);
};



#endif
