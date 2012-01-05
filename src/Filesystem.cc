
/* Filesystem.cc<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-05.
 * @Editor:      Vim
 */

#include "Filesystem.h"


//////////////////////////////////////////////////////////////////////////////
namespace Filesystem
{
    void PrintCwd()
    {
        int buf_size = 500;
        char* buffer = new char[buf_size];

        getcwd(buffer,  buf_size);
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

