
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
#include <iostream>
#include <fstream>

#include "DefineException.h"
#include "Filesystem.h"
#include "GenPropertyNew.h"

#define REPO_NAME ".emp"

DEFINE_FAST_EXCEPTION(CannotCreateRepoError,"Cannot create repository")
DEFINE_FAST_EXCEPTION(RepoExistentError,"A repository exists here")
DEFINE_FAST_EXCEPTION(PropExistentError,"Property exists already")
DEFINE_FAST_EXCEPTION(PropInvalidTypeError,"Created property has invalid type")

DEFINE_VAR_EXCEPTION(ExcRepository)


/** class which manages the Repository
 */
class Repository
{
    private:
    std::string mRepoName;
    std::string mAbsoluteRepoPath;
    std::list<GenPropertyBase*> PropertyList;

    
    public:
    Repository();
    ~Repository();
    
    bool IsOnTheRun();
    
    static bool IsExistent();
    //static PropertyTypes GetPropTypeFromStr(std::string const& str);

    /* actions */
    void Init();

    void AddProperty(std::string const& key, std::string const& type, std::string const& value);
    
    void RemoveProperty(std::string rPath, std::string const& key);
    void RemovePropertyClass(std::string const& key);
    void RemovePropertyClassAndInstances(std::string const& key);



    void Load();

    
    /* io */
    void CreatePropertyClass(std::string const& key, std::string const& rType);
    void ReadMetaDataFromFile(std::string const& rPath, std::string& rKey, std::string& rType);

    void ReadPropDataFromFile(std::string const& rPath, GenPropertyBase* pProp);
    void WritePropDataToFile(std::string const& rPath, GenPropertyBase* pProp);




    std::list<GenPropertyBase*> GetPropertyList(){ return this->PropertyList; };

    GenPropertyBase* CreatePropertyFromTypeString(std::string const& rType);
};



#endif
