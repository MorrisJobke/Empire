
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
#include "GenProperty.h"
#include "RegexHelper.h"

#define REPO_NAME ".emp"

DEFINE_FAST_EXCEPTION(CannotCreateRepoError,"Cannot create repository")
DEFINE_FAST_EXCEPTION(RepoExistentError,"A repository exists here")
DEFINE_FAST_EXCEPTION(PropExistentError,"Property exists already")
DEFINE_FAST_EXCEPTION(PropInvalidTypeError,"Created property has invalid type")
DEFINE_FAST_EXCEPTION(PropNotExists, "Property not exists.")
DEFINE_FAST_EXCEPTION(PropClassNotExists, "PropertyClass not exists.")
DEFINE_FAST_EXCEPTION(PropClassExistsWithOtherKey, "PropertyClass exists with an other key already.")
DEFINE_FAST_EXCEPTION(PropClassCreateError, "Cannot create PropertyClass.")

DEFINE_VAR_EXCEPTION(ExcRepository)


/** class which manages the Repository
 */
class Repository
{
    private:
    std::string mRepoName;
    std::string mAbsoluteRepoPath;
    std::list<GenPropertyBase*> mPropertyList;
    std::list<GenPropertyBase*> mCwdPropertyList;

    public:
    Repository();
    ~Repository();

    bool IsExistent();
    bool IsPropertyInCwd(std::string const& rKey);
    bool ContainsProperty(std::string const& rKey);
    bool IsCollectionInCwd(std::string const& rKey);
    bool IsCollection(std::string const& rKey);
    bool IsProperty(std::string const& rKey);
    GenPropertyBase* GetPropertyByKey(std::string const& rKey);
    std::string GetRepositoryPath();
    std::string GetMetaPath();
    std::string GetPropertyValue(std::string const& rKey);
    std::list<GenPropertyBase*> GetCreatedProperties();
    std::list<GenPropertyBase*> GetCollections();
    std::list<GenPropertyBase*> GetAddedProperties();

    //static PropertyTypes GetPropTypeFromStr(std::string const& str);

    /* actions */
    void Init();

    void AddProperty(std::string const& key, std::string const& type, std::string const& value);

    void RemoveProperty(std::string const& rKey);
    void RemovePropertyInList(std::string const& rKey);
    void RemovePropertyClass(std::string const& rKey);
    void RemovePropertyClassAndInstances(std::string const& rKey);



    void Load();


    /* io */
    void CreatePropertyClass(std::string const& key, std::string const& rType);
    void ReadMetaDataFromFile(std::string const& rPath, std::string& rKey, std::string& rType);

    void ReadPropDataFromFile(std::string const& rPath, GenPropertyBase* pProp);
    void WritePropDataToFile(std::string const& rPath, GenPropertyBase* pProp);



    /** getter for member attribute mPropertyList
     *
     * @return the list of properties
     */
    std::list<GenPropertyBase*> GetPropertyList(){ return this->mPropertyList; };

};

#endif
