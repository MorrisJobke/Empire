
/* PropertyFloat.cc
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-16.
 * @Editor:      Vim
 */

#include "PropertyFloat.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

PropertyFloat::PropertyFloat(double value)
{
    Init(value);
}

PropertyFloat::PropertyFloat(string const& key, double value)
{
    Init(key, value);
}

PropertyFloat::PropertyFloat(string const& key, string const& description, double value)
{
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
