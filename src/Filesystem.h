
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
#include <string>
#include <exception>

namespace Filesystem
{
    using namespace std;

    /** exceptions
     */
    class CannotCreateDirError
    { 
        private:
            string mWhat;

        public:
            CannotCreateDirError() 
            : mWhat("Cannot Create Directory")
            { }

            string what()
            {
                return mWhat;
            }
    };

    void PrintCwd();
    void CreateDirectory(string& rDirPath);
    bool DirectoryExists(string& rDirPath);
}


#endif
