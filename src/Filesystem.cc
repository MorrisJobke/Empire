
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
    /** function which prints the current working dir
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

    /** function which returns the current working dir
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

    /** function to change the cwd
     */
    bool ChangeCwd(string& rPath)
    {
        int ret = chdir(rPath.c_str());
        
        if (ret == -1)
            return false;
        else
            return true;
    }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

    /** function to create a new directory
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

    /** function to create a new directory
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
    
    /** function to write a string to File
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

    /** function to write a string to File
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
    /** function to check whether a file is existent
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



}
