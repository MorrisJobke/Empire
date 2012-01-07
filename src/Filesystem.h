
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
#include <errno.h>
#include <cstring>

#include <iostream>
#include <fstream>
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

    void PrintCwd();
    void CreateDirectory(string& rDirPath);
    bool DirectoryExists(string& rDirPath);

    void FileWriteString(string& rFilePath, string& rContent);
    bool FileExists(std::string& rPath);
}


#endif
