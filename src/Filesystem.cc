
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
        
        cout << buffer << endl;
        delete[] buffer;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
     /** 
     * @brief function wich returns the current working dir
     * @return returns the current working directory as string
     */ 
    string GetCwd()
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
        
        string ret = buffer;
        delete[] buffer;

        return ret;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
     /** 
     * @brief function to change the current working directory
     * @param rPath path of new working directory
     * @return returns true when cwd change succeeds, otherwise false
     */ 
    bool ChangeCwd(string const& rPath)
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
    void CreateDirectory (string const& rDirPath)
    {
        /* create char array */
        char* cstr = new char[rDirPath.size() + 1];
        strcpy(cstr, rDirPath.c_str());

        mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;

        int ret = mkdir(cstr, mode);
        
        delete[] cstr;

        if (ret != 0)
           throw CannotCreateDirError();

    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

     /** 
     * @brief function to check if a given directory exists
     * @param rDirPath path of directory
     * @return returns true when given directory exists, otherwise false
     */    
    bool DirectoryExists(string const& rDirPath)
    {
        /* create char array */
        char* cstr = new char[rDirPath.size() + 1];
        strcpy(cstr, rDirPath.c_str());

        struct stat sb;
        stat(cstr, &sb);

        delete[] cstr;

        if (S_ISDIR(sb.st_mode) != 0)
            return true;
        else
            return false;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** print out all dir entries
     */ 
    void PrintDirEntries(string const& rDirPath)
    {
        DIR *dp;
        struct dirent *ep;

        dp = opendir (rDirPath.c_str());
        if (dp != NULL)
        {
            while ((ep = readdir (dp)))
                cout << ep->d_name << endl;
            (void) closedir (dp);
        }
        else
            perror ("Couldn't open the directory");
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** remove the directory recursive
     * @param rPath path of the directory
     */ 
    void RemoveDirRec(string const& rPath)
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
     */ 
    int RemoveFile(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
    {
        int rv = remove(fpath);

        if (rv)
            perror(fpath);
        return rv;
    }


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
    
    /** 
     * @brief function to write a string to file
     * @param rFilePath path where string should be written
     * @param rContent  string that should be written
     */
    void FileWriteString(string const& rFilePath, string& rContent)
    {
        ofstream file;

        file.open(rFilePath.c_str());
        
        if (file.is_open())
        {
            file << rContent;
            file.close();
        }
        else
            throw CannotOpenFileError();
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

     /** 
     * @brief function to append a given string to a given file
     * @param rFilePath path of the file that should be appended
     * @param rContent string that will be appended to the given File
     */ 
    void FileAppendString(string const& rFilePath, string& rContent)
    {
        ofstream file;

        file.open(rFilePath.c_str(), ios::app);
        
        if (file.is_open())
        {
            file << rContent;
            file.close();
        }
        else
            throw CannotOpenFileError();
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

     /** 
     * @brief function to delete a given file
     * @param rFilePath path of the file that should be deleted
     */ 
    void FileDelete(string const& rFilePath)
    {       
        if (FileExists(rFilePath))
        {
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
    bool FileExists(string const& rPath)
    {
        /* create char array */
        char* cstr = new char[rPath.size() + 1];
        strcpy(cstr, rPath.c_str());

        struct stat sb;
        stat(cstr, &sb);

        delete[] cstr;

        if (S_ISREG(sb.st_mode) != 0)
            return true;
        else
            return false;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
    
    /** 
     * @brief function to read a file into string
     * @param rFilePath path where string should be written
     * @return string from file
     */
    std::string FileReadString(string const& rFilePath)
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
            throw CannotOpenFileError();

        return result;
    }
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

}
