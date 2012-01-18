
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
    std::string old_cwd = Fs::GetCwd();


    while(true)
    {
        std::string cwd;

        repo_found = Fs::DirectoryExists(repo_name);

        if (repo_found == true)
        {
            Fs::ChangeCwd(old_cwd);
            return true;
        }

        cwd = Fs::GetCwd();
        if (cwd == "/")
        {
            Fs::ChangeCwd(old_cwd);
            return false;
        }

        Fs::ChangeCwd(parent);
    }
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
        std::string cwd;

        repo_found = Fs::DirectoryExists(repo_name);

        if (repo_found == true)
        {
            this->mAbsoluteRepoPath = Fs::GetCwd();
            break;
        }

        cwd = Fs::GetCwd();
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
        throw ExcRepository("Err: Repo Exsists");


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

            PropertyIo::ReadMetaDataFromFile(this->mAbsoluteRepoPath + "/" + REPO_NAME + "/" + entry,
                    new_key, new_type);

            GenPropertyBase* p_new_prop = this->CreatePropertyFromTypeString(new_type);
            p_new_prop->SetKey(new_key);

            this->PropertyList.push_back(p_new_prop);
        }
        (void) closedir (dp);
    }
    else
        perror ("Couldn't open the directory");


    /*
     * now collect propery instances
     */

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
                if (entry == "." || entry == "..")
                    continue;

                /* search entry in the member property list */
                std::list<GenPropertyBase*>::const_iterator it;

                for (it = this->PropertyList.begin(); it != this->PropertyList.end(); it++)
                {
                    if ((*it)->GetKey() == entry)
                    {
                        //std::cout << "Try to load: " << entry << std::endl;
                        if (!(*it)->HasValue())
                            PropertyIo::ReadDataFromFile(entry, *it);
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
            Fs::ChangeCwd("..");
    }

    Fs::ChangeCwd(start_dir);

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** create a property from type-string
 */
GenPropertyBase* Repository::CreatePropertyFromTypeString(std::string const& rType)
{
    GenPropertyBase* p_new = NULL;

    if (rType == GetTypeName<int>())
        p_new = new GenProperty<int>();

    else if (rType == GetTypeName<double>())
        p_new = new GenProperty<double>();

    else if (rType == GetTypeName<float>())
        p_new = new GenProperty<float>();

    else if (rType == GetTypeName<std::string>())
        p_new = new GenProperty<std::string>();

    return p_new;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** method to add a new property class
 *
 * this creates a new metafile in the .emp folder with key as name and type as
 * content
 * @param the key
 * @param the type
 *
 * @pre the repo exits and mRepoName is not empty
 * @pre type string is valid
 */
void Repository::CreatePropertyClass(std::string const& key, std::string const& rType)
{

    /* TODO: check whether type is valid */

    /* check if repo exists */

    if (this->mAbsoluteRepoPath == "")
        throw ExcRepository("Err: Repo Not Exsists");


    /* check if property exists */

    //std::cout << "check for prop: " << this->mAbsoluteRepoPath + "/" + REPO_NAME + "/" + key << std::endl;

    if (Fs::FileExists(this->mAbsoluteRepoPath + "/" + REPO_NAME + "/" + key))
        throw ExcRepository("Err: Property exsists");

    PropertyIo::WriteMetaDataToDir(this->mAbsoluteRepoPath + "/" + REPO_NAME, key, rType);
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
    std::ifstream meta_file(rPath.c_str());

    if (meta_file.is_open())
    {
        if (meta_file.good())
        {
            std::getline(meta_file, rType);
        }
    }

    /* extract key */
    std::string key = rPath;
    std::string search_for = "/";

    std::size_t found;
    found = key.rfind(search_for);

    if ( found != std::string::npos)
        key.replace(0, found + 1,"");

    rKey = key;
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
    std::string file_path(rPath + "/" + pProp->GetKey());

    std::ofstream file(file_path.c_str());

    if (file.is_open())
    {
        file << pProp->ToString();
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** read property data from Filesystem
 *
 * @param rPath complete file path
 * @param pProp pointer to the property the data is written to
 */
void Repository::ReadPropDataFromFile(std::string const& rPath, GenPropertyBase* pProp)
{
    std::ifstream file(rPath.c_str());

    std::string buffer;

    if (file.is_open())
    {
        if (file.good())
        {
            std::getline(file, buffer);
        }
    }

    //std::cout << "Try to set from string: " << buffer << std::endl;

    /* string exception */
    if (pProp->GetTypeN() == GetTypeName<std::string>())
        ((GenProperty<std::string>*)pProp)->SetValue(buffer);
    else
        pProp->SetValueFromString(buffer);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** add a property with the given value, in the current wd
 *
 * This is only done if the property class exists
 * TODO: create property class on demand
 */
void Repository::AddProperty(std::string const& key, std::string const& type, std::string const& value)
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
