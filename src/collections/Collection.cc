
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
    error = 0;
}

//Entfernen?
Collection::Collection(string const& key, struct Propertylist *properties)
{
    //Collectionlist und auf Collections mit gleichen Key überprüfen  
    mKey = key;
    mPropertylist = properties;
    error = 0;
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

void Collection::RemoveProperty(BaseProperty property)
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

struct Propertylist *Collection::GetPropertylist() const
{
    return mPropertylist;
}

void Collection::SetPropertylist(struct Propertylist *properties)
{
    mPropertylist = properties;
}

int Collection::GetError() const
{
    return error;
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
