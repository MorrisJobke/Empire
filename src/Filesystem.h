
/* Filesystem.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-05.
 * @Editor:      Vim
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <unistd.h>
#include <errno.h>

#include <iostream>
#include <string>

namespace Filesystem
{
    void PrintCwd();
    void CreateDirectory();
}


#endif
