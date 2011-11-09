
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

/** Define the << operator
 *
 * @relates Contact
 * @param rOut reference to the output stream
 * @param rRule reference to a rule */
ostream& operator<<(ostream& rOut, const Contact& rContact)
{
    rContact.Print(rOut);
    return rOut;
}


/*============================= OPERATIONS =================================*/

void Invoice::Print()
{
    cout << mName << endl;
}
    

/** Move The Rule data to given stream.
 *
 * functon for use in the operator <<
 * @param rOut reference to the output stream */
void Contact::Print(ostream& rOut) const
{
    rOut << mName << endl;
    rOut << mStreet << " " << mStreetNr << endl;
    rOut << mZipCode << " " << mCity << endl;
}

/*============================= ACESS      =================================*/
/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
