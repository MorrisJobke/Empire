
/* invoice.cc<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-11-09.
 * @Editor:      Vim
 */

#include "invoice.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/** Constructor
 *
 */
Invoice::Invoice()
{
    mName = "Rech";
}


/** Destructor
 *
 */
Invoice::~Invoice()
{
}


/** Constructor
 *
 */
Contact::Contact()
:   mName("Don Joe"),
    mStreet("The Street"),
    mStreetNr(42),
    mZipCode("66666"),
    mCity("Wusterhausen")
{
}


/** Destructor
 *
 */
Contact::~Contact()
{
}


/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/
void Invoice::Print()
{
    cout << mName << endl;
}
    
/*============================= ACESS      =================================*/
/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
