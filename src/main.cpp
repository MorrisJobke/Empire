
/* main.cpp<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-11-09.
 * @Editor:      Vim
 */

#include "invoice.h"

int main()
{

    Invoice inv;
    inv.Print();

    Contact c;
    c.Print();

    string const& name = c.GetName();
    
    cout << name << endl;

    c.Print();
}

