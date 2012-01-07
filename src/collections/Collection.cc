
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
    mPropertyList = NULL;
}

/** Destructor
 *
 */
Collection::~Collection()
{
}


/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/


/*============================= ACCESS     =================================*/


/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
