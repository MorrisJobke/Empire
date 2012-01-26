
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
 */
Coll::Coll()
{
}

/** constructor
 *
 * @param rPath the directory where the directory should be read from
 */
Coll::Coll(std::string const& rPath)
:   mPath(rPath)
{
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** destructor
 */
Coll::~Coll()
{
}


/*============================= OPERATORS ==================================*/

std::ostream& operator<<(std::ostream& rOut, Coll rColl)
{
    rColl.ToOutStream(rOut);
    return rOut;
}

std::istream& operator>>(std::istream& rIn, Coll rColl)
{
    return rIn;
}

/*============================= OPERATIONS =================================*/

/** this method loads a collection from a DirectoryExists
 *
 * @param rPath path of the collection
 */
void Coll::Load(std::string const& rPath)
{
    this->mPath = rPath;

    if (Fs::DirectoryExists(rPath) == false)
        throw ErrorColl("COLL_NO_COLL_FOUND");

    /* load Collection from directory */

    std::list<GenPropertyBase*> dec_list;

    /* check declared dir and load */
    DIR *dp;
    struct dirent *ep;

    std::string dir_path = this->mPath + "/" + "0";
    dp = opendir (dir_path.c_str());
    if (dp != NULL)
    {
        while ((ep = readdir (dp)))
        {
            std::string entry = ep->d_name;

            /* skip standard links */
            if (entry == "." || entry == "..")
                continue;

            /* create new property read it and append it to list */
            std::string new_type;
            std::string new_key;

            PropertyIo::ReadMetaDataFromFile(this->mPath + "/" + "0" + "/" + entry,
                    new_key, new_type);

            GenPropertyBase* p_new_prop = PropertyHelpers::CreatePropertyFromTypeString(new_type);
            p_new_prop->SetKey(new_key);

            // std::cout << "read prop data: " << *p_new_prop << std::endl;

            dec_list.push_back(p_new_prop);
        }
        (void) closedir (dp);
    }
    else
        throw ErrorColl("COLL_NO_DEC_FOUND");

    this->mPropList.push_back(dec_list);


    /* if nessecary load other dirs */

    /* count dir entries */
    int dir_count = 0;

    dp = opendir (this->mPath.c_str());
    if (dp != NULL)
    {
        while ((ep = readdir (dp)))
        {
            std::string entry = ep->d_name;

            /* skip standard links */
            if (entry == "." || entry == "..")
                continue;

            dir_count++;

        }
        (void) closedir (dp);
    }
    else
        throw ErrorColl("COLL_NO_COLL_FOUND");

    /* scan data dirs */

    // std::cout << "Dir count " << dir_count << std::endl;

    for (int dir_idx = 1; dir_idx < dir_count; dir_idx++)
    {
        std::stringstream str;
        str << dir_idx;

        std::list<GenPropertyBase*> new_list;

        std::string dir_path = this->mPath + "/" + str.str();
        dp = opendir (dir_path.c_str());
        if (dp != NULL)
        {
            while ((ep = readdir (dp)))
            {
                std::string entry = ep->d_name;

                /* skip standard links */
                if (entry == "." || entry == "..")
                    continue;

                /* create new property read it and append it to list */
                std::string new_type;
                std::string new_key;

                /* load matching prop */
                PropertyIo::ReadMetaDataFromFile(this->mPath + "/" + "0" + "/" + entry,
                        new_key, new_type);

                GenPropertyBase* p_new_prop = PropertyHelpers::CreatePropertyFromTypeString(new_type);
                p_new_prop->SetKey(new_key);

                PropertyIo::ReadDataFromFile(this->mPath + "/" + str.str() + "/" + entry, p_new_prop);


                // std::cout << "read prop data: " << *p_new_prop << std::endl;

                new_list.push_back(p_new_prop);
            }
            (void) closedir (dp);
        }
        else
            throw ErrorColl("COLL_NO_DEC_FOUND");

        if (new_list.empty() == false)
        {
            // std::cout << "pushing data: " << std::endl;
            this->mPropList.push_back(new_list);
        }
    }
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** this creates the folder 0 with property types
 *
 * @param pPropList list with property members
 */
void Coll::Declare(std::list<GenPropertyBase*> const& pPropList)
{
    //std::list<GenPropertyBase*>::const_iterator print_it;
    //
    //std::cout << "declared properties\n" << std::endl;
    //for (print_it = pPropList.begin(); print_it != pPropList.end(); print_it++)
    //{
    //    std::cout << *(*print_it) << std::endl;
    //}

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

/** this creates a new numbered folder wth property data files
 *
 * @param pPropList list with property members
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

/** prints "This is a Collection" to the stream
 *
 * @param rOut the outstream where the data is printed
 */
void Coll::ToOutStream(std::ostream& rOut)
{
    rOut << "This is a Collection";
}

/** method for debugging. prints the content of the collection
 *
 */
void Coll::DebugPrint()
{
    int outer_count = 0;
    std::list< std::list<GenPropertyBase*> >::const_iterator outer;

    for (outer = this->mPropList.begin(); outer != this->mPropList.end(); outer++);
    {
        std::cout << outer_count << "{" << std::endl;

        std::list<GenPropertyBase*>::const_iterator inner;
        std::cout << "label" << std::endl;

        for (inner = outer->begin(); inner != outer->end(); inner++)
        {
            if ((*inner) == NULL)
                std::cout << "NULL" << std::endl;
            else
                std::cout << "   " << *(*inner) << std::endl;
        }

        std::cout << "}" << std::endl;
        outer_count++;
    }
}


/*============================= ACESS      =================================*/

/** getter for the propertylist of the collection
 *
 * @return returns the propertylist
 */

std::list< std::list<GenPropertyBase*> > Coll::GetList() const
{
    return this->mPropList;
}

/** getter for the meta-data of the propertys
 *
 * @return returns a list of property keys
 */
std::list< GenPropertyBase* > Coll::GetPropertyList()
{
    std::list<GenPropertyBase*>::const_iterator it_meta;
    std::list<GenPropertyBase*> meta_list = this->mPropList.front();
    std::list<GenPropertyBase*> result;

    /* go through the 0th list entry and check types and existens */
    for (it_meta = meta_list.begin(); it_meta != meta_list.end(); it_meta++)
    {
        result.push_back(*it_meta);
    }

    return result;
}

/** get the count of data-rows in this collection
 *
 * @return returns a the count of rows
 */
int Coll::GetRowCount()
{
    return GetList().size() - 1;
}

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////