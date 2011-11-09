
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


/** Constructor
 *
 */
Contact::Contact(string name,
        string street,
        int    streetNr,
        string zipCode,
        string city)
:   mName(name),
    mStreet(street),
    mStreetNr(streetNr),
    mZipCode(zipCode),
    mCity(city)
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
    

void Contact::Print()
{
    cout << mName << endl;
    cout << mStreet << " " << mStreetNr << endl;
    cout << mZipCode << " " << mCity << endl;
}
/*============================= ACESS      =================================*/
/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
