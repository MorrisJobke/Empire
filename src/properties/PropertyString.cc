
/* PropertyString.cc
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#include "PropertyString.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

PropertyString::PropertyString(string const& key, string value)
{
    SetType("String");
    Init(key, value);
}

PropertyString::PropertyString(string const& key, string const& description, string value)
{
    SetType("String");
    Init(key, description, value);
}

PropertyString::~PropertyString()
{
}

/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/
/*============================= ACESS      =================================*/
/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
