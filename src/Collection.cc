
/* Collection.cc
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-18.
 * @Editor:      Vim
 */

#include "Collection.h"

namespace Fs = Filesystem;


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/** constructor
 *
 * @param the directory where the directory should be read from
 */
Coll(std::string const& rPath)
:   mPath(rPath)
{
    /* load Collection from directory */
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** destructor
 */
~Coll()
{
}


/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/

/* this creates the folder 0 with property types
 *
 * @param list with property members
 */
Declare(std::list<GenPropertyBase*> const&)
{
    if (!mPropList.empty())
        throw ErrorColl("COLL_ALREADY_DECLARED");

    if (Fs::DirectoryExists(rPath + "/" + "0"))
        throw ErrorColl("COLL_DECLARE_DIR_EXISTS");

    /* create the declare dir */
    Fs::CreateDirectory(rPath + "/" + "0");
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/* this creates a new numbered folder wth property data files
 *
 * @param list with property members
 */
AddRow(std::list<GenPropertyBase*> const&)
{
}

/*============================= ACESS      =================================*/

std::list<std::list<GenPropertyBase*>> GetList() const
{
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////

void WriteToDir(std::string const& rPath)
{
}
