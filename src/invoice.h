
/* invoice.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-11-09.
 * @Editor:      Vim
 */

#ifndef INVOICE_H
#define INVOICE_H

#include <string>
#include <iostream>
using namespace std;


/** class to describe a contact
 *
 */
class Contact
{
private:
    string  mName;
    string  mStreet;
    int     mStreetNr;
    string  mZipCode;
    string  mCity;

public:
    Contact();
    ~Contact(); 

    Contact(string name,
            string street,
            int    streetNr,
            string zipCode,
            string city);

    void Print();

    /* getter */
    string  const& GetName()        {return mName;};
    string  const& GetStreet()      {return mStreet;};
    int     const& GetStreetNr()    {return mStreetNr;};
    string  const& GetZipCode()     {return mZipCode;};
    string  const& GetCity()        {return mCity;};

};


/** This class represents the main data type for an invoice
 *
 */ 
class Invoice
{
private:
    string mName;
    Contact mRecipient;
    Contact mSender;
    
public:
    Invoice();
    ~Invoice();

    void Print();
};


#endif
