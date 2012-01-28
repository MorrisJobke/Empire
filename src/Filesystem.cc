
/* Filesystem.cc<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-05.
 * @Editor:      Vim
 */

#include "Filesystem.h"

using namespace std;


//////////////////////////////////////////////////////////////////////////////
namespace Filesystem
{
     /**
     * @brief function wich prints the current working directory
     */
    void PrintCwd()
    {
        int buf_grain = 10;
        int buf_size = 10;

        char* buffer;

        while (true)
        {
           buffer = new char[buf_size];
           buffer = getcwd(buffer,  buf_size);

           if (buffer == NULL and errno == ERANGE)
           {
               delete[] buffer;
               buf_size += buf_grain;
           }
           else
               break;
        }

        std::cout << buffer << std::endl;
        delete[] buffer;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
     /**
     * @brief function wich returns the current working dir
     * @return returns the current working directory as string
     */
    std::string GetCwd()
    {
        int buf_grain = 10;
        int buf_size = 10;

        char* buffer;

        while (true)
        {
           buffer = new char[buf_size];
           buffer = getcwd(buffer,  buf_size);

           if (buffer == NULL and errno == ERANGE)
           {
               delete[] buffer;
               buf_size += buf_grain;
           }
           else
               break;
        }

        std::string ret = buffer;
        delete[] buffer;

        return ret;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
     /**
     * @brief function to change the current working directory
     * @param rPath path of new working directory
     * @return returns true when cwd change succeeds, otherwise false
     */
    bool ChangeCwd(std::string const& rPath)
    {
        int ret = chdir(rPath.c_str());

        if (ret == -1)
            return false;
        else
            return true;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

     /**
     * @brief function to create a new directory
     * @param rDirPath path of the new directory
     */
    void CreateDirectory (std::string const& rDirPath)
    {
        /* create char array */
        char* cstr = new char[rDirPath.size() + 1];
        strcpy(cstr, rDirPath.c_str());

        mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;

        int ret = mkdir(cstr, mode);

        delete[] cstr;

        if (ret != 0)
        {
            if (errno == EACCES)
                std::cout << "errno: EACCES" << std::endl;
            if (errno == EEXIST)
                std::cout << "errno: EEXIST" << std::endl;
            if (errno == EMLINK)
                std::cout << "errno: ENOSPC" << std::endl;
            if (errno == EROFS)
                std::cout << "errno: EROFS" << std::endl;
            throw CannotCreateDirError();
        }

    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

     /**
     * @brief function to create a new directory recursively
     * @param rDirPath path of the new directory
     */
    void CreateDirectoryRec (std::string const& rDirPath)
    {
        // extract base
        std::string base = GetParentFolderPath(rDirPath);

        if (base != "")
            CreateDirectoryRec(base);

        if (!DirectoryExists(rDirPath))
            CreateDirectory(rDirPath);
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

     /**
     * @brief function to check if a given directory exists
     * @param rDirPath path of directory
     * @return returns true when given directory exists, otherwise false
     */
    bool DirectoryExists(std::string const& rDirPath)
    {
        /* create char array */
        char* cstr = new char[rDirPath.size() + 1];
        strcpy(cstr, rDirPath.c_str());

        int ret;

        //std::cout << "checking dir: " << rDirPath << std::endl;

        struct stat sb;
        ret = stat(cstr, &sb);
        if (ret != 0)
        {
            if (errno == ENOENT)
                return false;
        }


        delete[] cstr;

        if (S_ISDIR(sb.st_mode) != 0)
            return true;
        else
            return false;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** print out all dir entries
     * @param rDirPath path of the dir of which the entries should printed
     */
    void PrintDirEntries(std::string const& rDirPath)
    {
        DIR *dp;
        struct dirent *ep;

        dp = opendir (rDirPath.c_str());
        if (dp != NULL)
        {
            while ((ep = readdir (dp)))
                std::cout << ep->d_name << std::endl;
            (void) closedir (dp);
        }
        else
            perror ("Couldn't open the directory");
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** remove the directory recursive
     * @param rPath path of the directory
     */
    void RemoveDirRec(std::string const& rPath)
    {
        char* path = new char[rPath.size() + 1];
        strcpy(path, rPath.c_str());
        nftw(path, RemoveFile, 64, FTW_DEPTH | FTW_PHYS);
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** remove the file
     * @param fpath path of the file, which should deleted
     * @param sb pointer to the stat-struct with the file-informations of fpath
     * @param typeflag type of file, which should deleted
     * @param ftwbuf pointer to the ftw-struct with information about relative depth to starting point
     * @return returns 0, if the file is succesfully deleted
     */
    int RemoveFile(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
    {
        int rv = remove(fpath);

        if (rv)
            perror(fpath);
        return rv;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** remove all files with specified filename in the given directory recursively
     *
     * @param rName the name of the files
     * @param rDirPath directory where the files should be removed
     */
    void RemoveFilesInDirRec(std::string const& rName, std::string const& rDirPath)
    {
        std::list<std::string> dirPathsToDo;
        std::string currDir;

        dirPathsToDo.push_back(rDirPath);

        DIR *dp;
        struct dirent *ep;

        while(!dirPathsToDo.empty())
        {
            currDir = dirPathsToDo.front();
            dp = opendir (currDir.c_str());
            dirPathsToDo.pop_front();;

            //std::cout << "Scanning DIR: " << currDir << std::endl;
            if (dp != NULL)
            {
                while ((ep = readdir (dp)))
                {
                    std::string fileName = ep->d_name;
                    //std::cout << "Scanning File:" << fileName << std::endl;

                    //ignore . and ..
                    if(fileName == ".." || fileName == ".")
                        continue;

                    if (ep->d_type == DT_DIR)
                    {
                        //std::cout << "Putting dir on list: " << currDir + "/" + fileName << std::endl;
                        dirPathsToDo.push_back(currDir + "/" + fileName);
                    }
                    else if (fileName == rName)
                    {
                        //std::cout << "Deleting: " << currDir + "/" + fileName << std::endl;
                        FileDelete(currDir + "/" + fileName);
                    }
                }
                (void) closedir (dp);
            }
            else
                perror ("Couldn't open the directory");
        }
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** remove all directories with specified name in the given directory recursively
     *
     * @param rName the name of the dir
     * @param rDirPath directory where the directories should be removed
     */
    void RemoveDirsInDirRec(std::string const& rName, std::string const& rDirPath)
    {
        std::list<std::string> dirPathsToDo;
        std::string currDir;

        dirPathsToDo.push_back(rDirPath);

        DIR *dp;
        struct dirent *ep;

        while(!dirPathsToDo.empty())
        {
            currDir = dirPathsToDo.front();
            dp = opendir (currDir.c_str());
            dirPathsToDo.pop_front();;

            //std::cout << "Scanning DIR: " << currDir << std::endl;
            if (dp != NULL)
            {
                while ((ep = readdir (dp)))
                {
                    std::string fileName = ep->d_name;
                    //std::cout << "Scanning File:" << fileName << std::endl;

                    //ignore . and ..
                    if(fileName == ".." || fileName == ".")
                        continue;

                    if (ep->d_type == DT_DIR)
                    {
                        if (fileName == rName)
                        {
                            //std::cout << "Deleting: " << currDir + "/" + fileName << std::endl;
                            RemoveDirRec(currDir + "/" + fileName);
                        }
                        else
                        {
                            //std::cout << "Putting dir on list: " << currDir + "/" + fileName << std::endl;
                            dirPathsToDo.push_back(currDir + "/" + fileName);

                        }
                    }
                }
                (void) closedir (dp);
            }
            else
                perror ("Couldn't open the directory");
        }
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /**
     * @brief function to write a string to file
     * @param rFilePath path where string should be written
     * @param rContent  string that should be written
     */
    void FileWriteString(std::string const& rFilePath, std::string const& rContent)
    {
        std::ofstream file;

        file.open(rFilePath.c_str());

        if (file.is_open())
        {
            file << rContent;
            file.close();
        }
        else
            throw CannotOpenFileError(" " + rFilePath + " FileWriteString");
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

     /**
     * @brief function to append a given string to a given file
     * @param rFilePath path of the file that should be appended
     * @param rContent string that will be appended to the given File
     */
    void FileAppendString(std::string const& rFilePath, std::string const& rContent)
    {
        std::ofstream file;

        file.open(rFilePath.c_str(), ios::app);

        if (file.is_open())
        {
            file << rContent;
            file.close();
        }
        else
            throw CannotOpenFileError(" " + rFilePath + " FileAppendString");
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

     /**
     * @brief function to delete a given file
     * @param rFilePath path of the file that should be deleted
     */
    void FileDelete(std::string const& rFilePath)
    {
        if (FileExists(rFilePath))
        {
            remove(rFilePath.c_str());
            //recheck:
            if (FileExists(rFilePath))
                remove(rFilePath.c_str());
        }
        else
            throw CannotFindFileError();
    }


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
    /**
     * @brief function to check wether a given file exists
     * @param rPath path of file
     * @return returns true when given file exists, otherwise false
     */
    bool FileExists(std::string const& rPath)
    {
        bool result;
        ifstream ifile(rPath.c_str());
        result = ifile.good();
        ifile.close();
        return result;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /**
     * @brief function to read a file into string
     * @param rFilePath path where string should be written
     * @return string from file
     */
    std::string FileReadString(std::string const& rFilePath)
    {
        std::string result = "";
        std::string line;
        std::ifstream myfile(rFilePath.c_str());

        if (myfile.is_open())
        {
            while (myfile.good())
            {
                getline (myfile,line);
                if (result.compare(""))
                    result += "\n";
                result += line;
            }
            myfile.close();
        }
        else
            throw CannotOpenFileError(" " + rFilePath + " FileReadString");

        return result;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /**
     * @brief function to get the parent dir from a given string
     * @param rPath path from the given dir
     * @return parent dir as std::string
     */
    std::string GetParentFolderPath(std::string const& rPath)
    {
         int found = rPath.find_last_of("/");
         if (found == std::string::npos)
            return "";

         std::string result = rPath.substr(0, found);

        return result;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /**
     * @brief function to get the parent dir from a given string
     * @param rPath path from the given dir
     * @return parent dir as std::string
     */
    std::string GetFileNameFromPath(std::string const& rPath)
    {
         int found = rPath.find_last_of("/");
         if (found == std::string::npos)
            return rPath;

         std::string result = rPath.substr(found + 1, rPath.length());

        return result;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /**
     * @brief function to get the parent dir from a given string
     * @param rPath path from the given dir
     * @return parent dir as std::string
     */
    int GetFileType(std::string const& rPath)
    {
         std::string  path = GetParentFolderPath(rPath);
         std::string file = GetFileNameFromPath(rPath);

         DIR *dp;
        struct dirent *ep;


        dp = opendir (path.c_str());
        if (dp != NULL)
        {
            while ((ep = readdir (dp)))
            {
                if(ep->d_name == file)
                    return ep->d_type;
            }
        }

        return -1;
    }
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
}
