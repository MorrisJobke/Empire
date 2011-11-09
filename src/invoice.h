
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


/** This class represents the main data type for an invoice
 *
 */ 
class Invoice
{
private:
    string mName;
    
public:
    Invoice();
    ~Invoice();

    void Print();
};

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

    void Print();

    /* getter */
    string const& GetName() {return mName;};

};

#endif
