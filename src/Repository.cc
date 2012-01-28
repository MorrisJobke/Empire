
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
 *
 * @return boolean
 */
bool Repository::IsExistent()
{
    if (this->mAbsoluteRepoPath != "")
        return true;
    return false;
}


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/** the constructor
 *
 * the constructor ever returns a new repo. Here we check exsistens of a repo
 * and write the absolute path
 */
Repository::Repository()
{
    bool repo_found = false;
    std::string parent = "..";
    std::string repo_name = REPO_NAME;
    std::string old_cwd = Fs::GetCwd();


    while(true)
    {
        std::string cwd = Fs::GetCwd();

        repo_found = Fs::DirectoryExists(repo_name);

        if (repo_found == true)
        {
            this->mAbsoluteRepoPath = cwd;
            break;
        }

        if (cwd == "/")
        {
            this->mAbsoluteRepoPath = "";
            break;
        }

        Fs::ChangeCwd(parent);
    }

    Fs::ChangeCwd(old_cwd);
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

/** crete a new Repository
 *
 * this creates the .emp folder, it throws exception if a repo exits
 * TODO default properties
 */
void Repository::Init()
{
    /* check if repo is already there */

    if (this->mAbsoluteRepoPath != "")
        throw ExcRepository("Err: Repo Exists");


    /* create the repo directory */

    try
    {
        Fs::CreateDirectory(Fs::GetCwd() + "/" + REPO_NAME);
    }
    catch(Fs::CannotCreateDirError &exc)
    {
        throw ExcRepository("Err: Cannot Create Repo");
    }

    //std::cout << "init Repo at: " << Fs::GetCwd() << std::endl;

    /* set absolute path */
    this->mAbsoluteRepoPath = Fs::GetCwd();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** load a repository
 *
 * this collects all properties in a list
 */
void Repository::Load()
{
    /* repo check */

    if (this->mAbsoluteRepoPath == "")
        throw ExcRepository("ERR_REPO_NOTEXISTS");

    std::string start_dir = Fs::GetCwd();

    /* do not reload Repo */
    if (this->mPropertyList.empty() == false)
        return;

    /*
     * at first we collect meta properties ( property classes )
     */

    Fs::ChangeCwd(this->mAbsoluteRepoPath);
    //std::cout << "Loading Repo at: " << this->mAbsoluteRepoPath << std::endl;

    DIR *dp;
    struct dirent *ep;

    dp = opendir (REPO_NAME);
    if (dp != NULL)
    {
        while ((ep = readdir (dp)))
        {
            std::string entry = ep->d_name;

            /* skip standard links */
            if (entry == "." || entry == "..")
                continue;

            /* create new property read it and append it to list */
            std::string new_type;
            std::string new_key;

            this->ReadMetaDataFromFile(this->mAbsoluteRepoPath + "/" + REPO_NAME + "/" + entry,
                        new_key, new_type);

            GenPropertyBase* p_new_prop = PropertyHelpers::CreatePropertyFromTypeString(new_type);
            p_new_prop->SetKey(new_key);

            //std::cout << "loaded metadata: " << *p_new_prop << std::endl;

            this->mPropertyList.push_back(p_new_prop);
        }
        (void) closedir (dp);
    }
    else
        perror ("Couldn't open the directory");


    /*
     * now collect propery instances
     */
    bool startDir = true;
    Fs::ChangeCwd(start_dir);

    while(true)
    {
        /* get dir entries */
        dp = NULL;
        ep = NULL;

        dp = opendir (".");
        if (dp != NULL)
        {
            while ((ep = readdir (dp)))
            {
                std::string entry = ep->d_name;

                /* skip standard links */
                if (entry == "." || entry == ".." || entry == REPO_NAME)
                    continue;

                /* search entry in the member property list */
                std::list<GenPropertyBase*>::const_iterator it;

                for (it = this->mPropertyList.begin(); it != this->mPropertyList.end(); it++)
                {
                    if ((*it)->GetKey() == entry)
                    {
                        if(startDir)
                            this->mCwdPropertyList.push_back(*it);
                        //std::cout << "Try to load: " << entry << std::endl;
                        if (!(*it)->HasValue())
                        {
                            PropertyIo::ReadDataFromFile(entry, *it);
                            break;
                        }
                    }
                }
            }
            (void) closedir (dp);
        }
        else
            perror ("Couldn't open the directory");

        if (this->mAbsoluteRepoPath == Fs::GetCwd())
            break;
        else
        {
            startDir = false;
            Fs::ChangeCwd("..");
            //std::cout << "moving to .." << std::endl;
        }

    }

    Fs::ChangeCwd(start_dir);

    /* load collections */
    std::list<GenPropertyBase*>::iterator it;

    for (it = this->mPropertyList.begin(); it != this->mPropertyList.end(); it++)
    {
       if (!(*it)->HasValue() && (*it)->GetTypeN() == GetTypeName<Coll>())
       {
            GenProperty<Coll>* c_prop = (GenProperty<Coll>*)(*it);
            std::string key = c_prop->GetKey();
            Coll c(key);
            c.Load(key, this->GetMetaPath());
            c_prop->SetValue(c);
       }
    }

    /* print out loaded properties */
    // std::list<GenPropertyBase*>::iterator it;

    // std::cout << "Loaded properties\n" << std::endl;
    // for (it = this->mPropertyList.begin(); it != this->mPropertyList.end(); it++)
    // {
    //    if ((*it) == NULL)
    //    {
    //        std::cout << "NULL\n" << std::endl;
    //        continue;
    //    }
    //    std::cout << *(*it) << std::endl;
    // }

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** method to add a new property class
 *
 * this creates a new metafile in the .emp folder with key as name and type as
 * content
 * @param key the key
 * @param rType the type
 *
 * @pre the repo exits and mRepoName is not empty
 * @pre type string is valid
 */
void Repository::CreatePropertyClass(std::string const& key, std::string const& rType)
{

    /* TODO: check whether type is valid */

    /* check if repo exists */

    if (this->mAbsoluteRepoPath == "")
        throw ExcRepository("REPO_NOT_EXISTS");

    /* check if property exists */

    //std::cout << "check for prop: " << this->mAbsoluteRepoPath + "/" + REPO_NAME + "/" + key << std::endl;

    if (this->ContainsProperty(key))
        throw PropExistentError();

    /* correct type conversion */
    GenPropertyBase* new_prop = PropertyHelpers::CreatePropertyFromTypeString(rType);

    PropertyIo::WriteMetaDataToDir(this->mAbsoluteRepoPath + "/" + REPO_NAME, key, new_prop->GetTypeN());

    delete new_prop;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** method to read a metadatafile
 *
 * @param rPath filepath
 * @param rKey reference the key to be filled
 * @param rType reference the type to be filled
 */
void Repository::ReadMetaDataFromFile(std::string const& rPath, std::string& rKey, std::string& rType)
{
    PropertyIo::ReadMetaDataFromFile(rPath, rKey, rType);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** write property data to file
 *
 * file name is determined by key
 *
 * @param rPath the directory path the file is written
 * @param pProp pointer to a base property
 */
void Repository::WritePropDataToFile(std::string const& rPath, GenPropertyBase* pProp)
{
    PropertyIo::WriteDataToDir(rPath, pProp);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** read property data from Filesystem
 *
 * @param rPath complete file path
 * @param pProp pointer to the property the data is written to
 */
void Repository::ReadPropDataFromFile(std::string const& rPath, GenPropertyBase* pProp)
{
    PropertyIo::ReadDataFromFile(rPath, pProp);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** add a property with the given value, in the current wd
 *
 * This is only done if the property class exists
 *
 * @param key the key of the property
 * @param type the type of the property
 * @param value the value of the property
 */
void Repository::AddProperty(std::string const& key, std::string const& type, std::string const& value)
{
    std::string tmp_type = type;

    if(!Fs::FileExists(key))
    {

        if (tmp_type == "string")
            tmp_type = GetTypeName<std::string>();

        if (tmp_type == "") //recognize type from value
        {
            if(RegexHelper::isInt(value))
                tmp_type = GetTypeName<int>();
            else if(RegexHelper::isFloat(value))
                tmp_type = GetTypeName<float>();
            else if(RegexHelper::isFunction(value))
                tmp_type = GetTypeName<FunctionType>();
            else
                tmp_type = GetTypeName<std::string>();
        }

        /* check if Propertyclass exists already, otherwise create it*/
        if(!this->ContainsProperty(key))
        {
            try
            {
                this->CreatePropertyClass(key, tmp_type);
            }
            catch(ExcRepository exc)
            {
                throw PropClassCreateError();
            }
        }
        else //check if existing propertyClass is ok
        {
            this->Load();

            std::string fileType = this->GetPropertyByKey(key)->GetTypeN();

            //remove existing property from list:
            this->RemovePropertyInList(key);

            if(fileType != tmp_type)
                throw PropClassExistsWithOtherKey();
        }

        GenPropertyBase* p_new_prop = PropertyHelpers::CreatePropertyFromTypeString(tmp_type);
        p_new_prop->SetKey(key);
        p_new_prop->SetValueFromString(value);
        this->mPropertyList.push_back(p_new_prop);
        this->WritePropDataToFile(Fs::GetCwd(), p_new_prop);
    }
    else
        throw PropExistentError();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** delete property from Filesystem
 *
 * @param rKey complete file path
 */
void Repository::RemoveProperty(std::string const& rKey)
{
    this->Load();
    if(this->IsPropertyInCwd(rKey))
    {
        try
        {
            if (this->IsCollectionInCwd(rKey))
            {
                Fs::RemoveDirRec(rKey);
            }
            else
            {
                Fs::FileDelete(rKey);
            }
        }
        catch(Fs::CannotFindFileError const& e)
        {
            throw PropNotExists();
        }
    }
    else
    {
        throw PropNotExists();
    }
}

/** delete the given property from the list
 *
 * @param rKey key of the property which should deleted
 */

void Repository::RemovePropertyInList(std::string const& rKey)
{
    if(this->ContainsProperty(rKey))
    {
        std::list<GenPropertyBase*>::iterator it;

        for (it = this->mPropertyList.begin(); it != this->mPropertyList.end(); it++)
        {
            if ((*it)->GetKey() == rKey)
            {
                it = this->mPropertyList.erase(it);
                --it;
            }
        }
    }
    else
        throw PropNotExists();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** delete metadata from Filesystem
 *
 * @param rKey key name
 */
void Repository::RemovePropertyClass(std::string const& rKey)
{
    try
    {
        if (this->IsCollection(rKey))
        {
            Fs::RemoveDirRec(this->mAbsoluteRepoPath + "/" + REPO_NAME + "/" + rKey);
        }
        else
        {
            Fs::FileDelete(this->mAbsoluteRepoPath + "/" + REPO_NAME + "/" + rKey);
        }
    }
    catch(Fs::CannotFindFileError const& e)
    {
        throw PropClassNotExists();
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** delete metadata & all propertys with the given key from filesystem
 *
 * @param rKey the key of the property to remove
 */
void Repository::RemovePropertyClassAndInstances(std::string const& rKey)
{
    if (this->ContainsProperty(rKey))
    {
        if (this->IsCollection(rKey))
        {
            //remove all instances and property class
            Fs::RemoveDirsInDirRec(rKey, this->mAbsoluteRepoPath);
        }
        else
        {
            //remove all instances and property class
            Fs::RemoveFilesInDirRec(rKey, this->mAbsoluteRepoPath);
        }

        //remove from property list
        this->RemovePropertyInList(rKey);
    }
    else
    {
        throw PropClassNotExists();
    }
}

/*============================= ACCESS      =================================*/

/** check existance of property with the given key
 *
 * @param key the key of the property to check for
 *
 * @return boolean
 */
bool Repository::ContainsProperty(std::string const& key)
{
    std::list<GenPropertyBase*>::const_iterator it;

    for (it = this->mPropertyList.begin(); it != this->mPropertyList.end(); it++)
    {
        if ((*it)->GetKey() == key)
        {
            return true;
        }
    }

    return false;
}

/** checks if the given property key is from a property with value in current working dir
 *
 * @param rKey the key of the property wanted
 * @return boolean
 */
bool Repository::IsPropertyInCwd(std::string const& rKey)
{
    std::list<GenPropertyBase*>::const_iterator it;
    for (it = this->mCwdPropertyList.begin(); it != this->mCwdPropertyList.end(); it++)
        if((*it)->GetKey() == rKey)
            return true;
    return false;
}

/** checks if the given property key is from a Property
 *
 * @param rKey the key of the property wanted
 * @return boolean
 */
bool Repository::IsProperty(std::string const& rKey)
{
    std::list<GenPropertyBase*>::const_iterator it;
    for (it = this->mCwdPropertyList.begin(); it != this->mCwdPropertyList.end(); it++)
        if((*it)->GetKey() == rKey)
            return (*it)->GetTypeN() != GetTypeName<Coll>();
    return false;
}

/** checks if the given property key is from a Collection in Cwd
 *
 * @param rKey the key of the property wanted
 * @return boolean
 */
bool Repository::IsCollectionInCwd(std::string const& rKey)
{
    std::list<GenPropertyBase*>::const_iterator it;
    for (it = this->mCwdPropertyList.begin(); it != this->mCwdPropertyList.end(); it++)
        if((*it)->GetKey() == rKey)
            return (*it)->GetTypeN() == GetTypeName<Coll>();
    return false;
}

/** checks if the given property key is from a Collection
 *
 * @param rKey the key of the property wanted
 * @return boolean
 */
bool Repository::IsCollection(std::string const& rKey)
{
    std::list<GenPropertyBase*>::const_iterator it;
    for (it = this->mPropertyList.begin(); it != this->mPropertyList.end(); it++)
        if((*it)->GetKey() == rKey)
            return (*it)->GetTypeN() == GetTypeName<Coll>();
    return false;
}

/** returns the property containing the given key
 *
 * @param key the key of the property wanted
 *
 * @return GenPropertyBase*
 */
GenPropertyBase* Repository::GetPropertyByKey(std::string const& key)
{
    std::list<GenPropertyBase*>::const_iterator it;

    for (it = this->mPropertyList.begin(); it != this->mPropertyList.end(); it++)
    {
        if ((*it)->GetKey() == key)
        {
            return (*it);
        }
    }

    return NULL;
}

/** returns the absolute repo path
 *
 * @return repo path as std::string
 */
std::string Repository::GetRepositoryPath()
{
    return this->mAbsoluteRepoPath;
}

/** returns the absolute meta path
 *
 * @return meta path as std::string
 */
std::string Repository::GetMetaPath()
{
    if (this->mAbsoluteRepoPath != "")
        return this->mAbsoluteRepoPath + "/" + REPO_NAME;
    return REPO_NAME;
}

/** iterates trough parent folders recursively and returns first matching value
 *
 * @param rKey key of the property
 * @return value as std::string
 */
std::string Repository::GetPropertyValue(std::string const& rKey)
{
    GenPropertyBase* prop = this->GetPropertyByKey(rKey);

    std::string type = prop->GetTypeN();
    if (type == GetTypeName<int>())
    {
        GenProperty<int>* cast_prop = (GenProperty<int>*) prop;
        std::stringstream str;
        str << (cast_prop->GetValue());
        return str.str();
    }
    else if (type == GetTypeName<float>())
    {
        GenProperty<float>* cast_prop = (GenProperty<float>*) prop;
        std::stringstream str;
        str << (cast_prop->GetValue());
        return str.str();
    }
    else if (type == GetTypeName<double>())
    {
        GenProperty<double>* cast_prop = (GenProperty<double>*) prop;
        std::stringstream str;
        str << (cast_prop->GetValue());
        return str.str();
    }
    else if (type == GetTypeName<std::string>())
    {
        GenProperty<std::string>* cast_prop = (GenProperty<std::string>*) prop;
        return cast_prop->GetValue();
    }
    else if (type == GetTypeName<FunctionType>())
    {
        GenProperty<FunctionType>* cast_prop = (GenProperty<FunctionType>*) prop;
        std::stringstream str;
        str << cast_prop->GetValue();
        return str.str();
    }
    return "";
}

/** get a list of propertys in the current working dir
 *
 * @return list of property keys
 */
std::list<GenPropertyBase*> Repository::GetAddedProperties()
{
    std::list<GenPropertyBase*> result;
    std::list<GenPropertyBase*>::const_iterator it;
    for (it = this->mPropertyList.begin(); it != this->mPropertyList.end(); it++)
    {
        if ((*it)->GetTypeN() != GetTypeName<Coll>())
        {
            if((*it)->HasValue())
                result.push_back(*it);
        }
    }
    return result;
}

/** get a list of collections in the current working dir
 *
 * @return list of collection keys
 */
std::list<GenPropertyBase*> Repository::GetCollections()
{
    std::list<GenPropertyBase*> result;
    std::list<GenPropertyBase*>::const_iterator it;
    for (it = this->mPropertyList.begin(); it != this->mPropertyList.end(); it++)
    {
        if((*it)->GetTypeN() == GetTypeName<Coll>())
            result.push_back(*it);
    }

    return result;
}

/** get a list of propertys in the current working dir that have no value
 *
 * @return list of property keys
 */
std::list<GenPropertyBase*> Repository::GetCreatedProperties()
{
    std::list<GenPropertyBase*> result;
    std::list<GenPropertyBase*>::const_iterator it;
    for (it = this->mPropertyList.begin(); it != this->mPropertyList.end(); it++)
    {
        if ((*it)->GetTypeN() != GetTypeName<Coll>())
        {
            if(!(*it)->HasValue())
               result.push_back(*it);
        }
    }

    return result;
}



/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
