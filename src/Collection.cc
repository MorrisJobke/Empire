
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
Coll::Coll(std::string const& rPath)
:   mPath(rPath)
{
    /* load Collection from directory */
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** destructor
 */
Coll::~Coll()
{
}


/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/

/* this creates the folder 0 with property types
 *
 * @param list with property members
 */
void Coll::Declare(std::list<GenPropertyBase*> const& pPropList)
{
    if (!mPropList.empty())
        throw ErrorColl("COLL_ALREADY_DECLARED");

    if (Fs::DirectoryExists(this->mPath + "/" + "0"))
        throw ErrorColl("COLL_DECLARE_DIR_EXISTS");

    /* create the declare dir */
    Fs::CreateDirectory(this->mPath);
    Fs::CreateDirectory(this->mPath + "/" + "0");

    /* create meta files */
    std::list<GenPropertyBase*>::const_iterator it;

    for (it = pPropList.begin(); it != pPropList.end(); it++)
    {
        PropertyIo::WriteMetaDataToDir(this->mPath + "/" + "0", (*it));
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/* this creates a new numbered folder wth property data files
 *
 * @param list with property members
 */
void Coll::AddRow(std::list<GenPropertyBase*> const&)
{
}

/*============================= ACESS      =================================*/

std::list< std::list<GenPropertyBase*> > Coll::GetList() const
{
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////

void Coll::WriteToDir(std::string const& rPath)
{
}
