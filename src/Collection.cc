
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

    /* append to the front of the member list */
    this->mPropList.push_back(pPropList);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/* this creates a new numbered folder wth property data files
 *
 * @param list with property members
 */
void Coll::AddRow(std::list<GenPropertyBase*> const& pPropList)
{
    /* scan all entries */
    
    //std::cout << "Adding Row. Entries: " << pPropList.size() << std::endl;
    std::list<GenPropertyBase*>::const_iterator it;

    std::list<GenPropertyBase*> new_row;

    for (it = pPropList.begin(); it != pPropList.end(); it++)
    {
        std::list<GenPropertyBase*>::const_iterator it_meta;
        std::list<GenPropertyBase*> meta_list = this->mPropList.front();

        //std::cout << meta_list.size() << std::endl;


        bool found_entry = false;

        /* go through the 0th list entry and check types and existens */
        for (it_meta = meta_list.begin(); it_meta != meta_list.end(); it_meta++)
        {
            //std::cout << "Compare " << *it << " and " << *it_meta << std::endl;
            if ((*it)->GetKey() == (*it_meta)->GetKey())
            {
                if ((*it)->GetTypeN() == (*it_meta)->GetTypeN())
                {
                    found_entry = true;
                    //std::cout << "Prop Match " << *it << std::endl;
                    break;

                }
                else
                {
                    throw ErrorColl("COLL_TYPE_MISSMATCH_IN_ROW");
                }
            }
        }

        /* case if we validated the property */
        if (found_entry == true)
        {
            /* calculate the row idx */
            int idx = this->mPropList.size();
            std::stringstream str;
            str << idx;

            /* create the row-dir if neccesary */
            if (Fs::DirectoryExists(this->mPath + "/" + str.str()) == false)
            {
                Fs::CreateDirectory(this->mPath + "/" + str.str());
            }

            /* write prop data */
            PropertyIo::WritePropDataToDir(this->mPath + "/" + str.str(), (*it));

            /* append prop to row structure */
            new_row.push_back((*it));
        }
        

    }

    /* append the filled list if not empty */
    if (new_row.empty() == false)
        this->mPropList.push_back(new_row);

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
