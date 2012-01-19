
/* Filesystem.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-05.
 * @Editor:      Vim
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <cstring>

#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <exception>

#include "DefineException.h"

namespace Filesystem
{
    using namespace std;

    /** exceptions
     */
    DEFINE_FAST_EXCEPTION(CannotCreateDirError, "Cannot create directory.")
    DEFINE_FAST_EXCEPTION(CannotOpenFileError, "Cannot create file.")
    DEFINE_FAST_EXCEPTION(CannotFindFileError, "File not exists.")

    void PrintCwd();
    string GetCwd();
    bool ChangeCwd(string const& rPath);

    void CreateDirectory(string const& rDirPath);
    bool DirectoryExists(string const& rDirPath);
    void PrintDirEntries(string const& rDirPath);

    void FileWriteString(string const& rFilePath, string& rContent);
    void FileAppendString(string const& rFilePath, string& rContent);
    void FileDelete(string const& rFilePath);
    bool FileExists(std::string const& rPath);
    
    std::string FileReadString(string const& rFilePath);
}


#endif
