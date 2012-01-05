
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


}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

