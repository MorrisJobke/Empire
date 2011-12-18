
/* Collection.cc
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#include "Collection.h"



/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/** Constructor
 *
 */
Collection::Collection(string const& key)
{
    //Collectionlist und auf Collections mit gleichen Key überprüfen
    mKey = key;
    mPropertylist = NULL;
}

/** Destructor
 *
 */
Collection::~Collection()
{
}


/*============================= OPERATORS ==================================*/

void Collection::AddProperty(BaseProperty property)
{
}

void Collection::RemoveProperty(string const& key)
{
}

/*============================= OPERATIONS =================================*/
/*============================= ACESS      =================================*/

string Collection::GetKey() const
{
    return mKey;
}

void Collection::SetKey(string value)
{
    mKey = value;
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////