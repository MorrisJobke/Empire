
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
Collection::Collection()
{
}

/** Destructor
 *
 */
Collection::~Collection()
{
}

/** Init
 *
 */
void Collection::Init(string const& key)
{
    mKey = key;
    mPropertylist = NULL;
}

void Collection::Init(string const& key, struct Propertylist *properties)
{
    mKey = key;
    mPropertylist = properties;
}


/*============================= OPERATORS ==================================*/

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

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
