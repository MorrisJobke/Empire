
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

    Contact c("Hans Peter", "Prollweg", 13, "09666", "Wusterhausen");

    string const& name = c.GetName();

    cout << c;
    

}

