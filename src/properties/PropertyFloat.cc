
/* PropertyFloat.cc
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#include "PropertyFloat.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

PropertyFloat::PropertyFloat(string const& key, double value)
{
    SetType("Float");
    Init(key, value);
}

PropertyFloat::PropertyFloat(string const& key, string const& description, double value)
{
    SetType("Float");    
    Init(key, description, value);
}

PropertyFloat::~PropertyFloat()
{
}

/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/
/*============================= ACESS      =================================*/
/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
