
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
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <cstring>
#include <ftw.h>
#include <list>

#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <exception>

#include "DefineException.h"

/** some functions for interacting with the file system
 */
namespace Filesystem
{
    /** exceptions
     */
    DEFINE_FAST_EXCEPTION(CannotCreateDirError, "Cannot create directory.")
    DEFINE_FAST_EXCEPTION(CannotOpenFileError, "Cannot open file.")
    DEFINE_FAST_EXCEPTION(CannotFindFileError, "File not exists.")

    void PrintCwd();
    std::string GetCwd();
    bool ChangeCwd(std::string const& rPath);

    void CreateDirectory(std::string const& rDirPath);
    void CreateDirectoryRec(std::string const& rDirPath);
    bool DirectoryExists(std::string const& rDirPath);
    void PrintDirEntries(std::string const& rDirPath);
    void RemoveDirRec(std::string const& rPath);
    int RemoveFile(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf);
    void RemoveFilesInDirRec(std::string const& rName, std::string const& rDirPath);
    void RemoveDirsInDirRec(std::string const& rName, std::string const& rDirPath);

    void FileWriteString(std::string const& rFilePath, std::string const& rContent);
    void FileAppendString(std::string const& rFilePath, std::string const& rContent);
    void FileDelete(std::string const& rFilePath);
    bool FileExists(std::string const& rPath);

    std::string FileReadString(std::string const& rFilePath);
    std::string GetParentFolderPath(std::string const& rPath);
    std::string GetFileNameFromPath(std::string const& rPath);
    int GetFileType(std::string const& rPath);

    struct tm* GetFileCreationDate(std::string const& rPath);
}


#endif
