
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
            return true;
        
        cwd = Fs::GetCwd();
        if (cwd == "/")
            return false;

        Fs::ChangeCwd(parent);
    }
    Fs::ChangeCwd(old_cwd);
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
    
    std::cout << "init Repo at: " << Fs::GetCwd() << std::endl;

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

}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** method to add a new property class
 *
 * thsi creates a new metafile in the .emp folder with key as name and type as
 * content
 * @param the key
 * @param the type
 *
 * @pre the repo exits and mRepoName is not empty
 */
void Repository::CreatePropertyClass(std::string const& key, std::string const& type)
{
    /* check if repo exists */

    if (this->mAbsoluteRepoPath == "")
        throw ExcRepository("Err: Repo Not Exsists");


    /* check if property exists */
    
    //std::cout << "check for prop: " << this->mAbsoluteRepoPath + "/" + REPO_NAME + "/" + key << std::endl;
    //
    if (Fs::FileExists(this->mAbsoluteRepoPath + "/" + REPO_NAME + "/" + key))
        throw ExcRepository("Err: Property exsists");


    /* create and write metadata property */

    PropertyTypes new_type = GenProperty::StringToEnumType(type);
    if (new_type == UNDEFINED_T)
        throw ExcRepository("Err: Invalid Property Type");

    GenProperty new_prop(new_type, key);
    new_prop.WriteMetadata(this->mAbsoluteRepoPath + "/" + REPO_NAME);
}

/*============================= ACESS      =================================*/

bool Repository::IsOnTheRun()
{
    return true;
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
