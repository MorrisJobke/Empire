
/* ListHelper.cc
 * @Author:      rbs (rbs@hrz.tu-chemnitz.de)
 * @License:     GPL
 * @Created:     2012-01-22
 * @Editor:      Sublime Text 2
 */

#include "ListHelper.h"

//////////////////////////////////////////////////////////////////////////////
namespace ListHelper
{
    /** compares to lists of strings
     *
     * @param rList1 first list
     * @param rList2 secound list
     * @param rNotFound if true: returns all elements contained by rList1, but not by rList2,
     *                  if false: returns all elements contained by rList1 and rList2
     * @return result list
     */
    std::list<std::string> ListCompare(std::list<std::string> const& rList1, std::list<std::string> const& rList2, bool rNotFound)
    {
        std::list<std::string> result;
        std::list<std::string>::const_iterator it, it2;
        bool found;

        for (it = rList1.begin(); it != rList1.end(); it++)
        {
            found = false;
            for (it2 = rList2.begin(); it2 != rList2.end(); it2++)
            {
                if (*it2 == *it)
                {
                    found = true;
                    break;
                }
            }
            if (found != rNotFound)
                result.push_back(*it);
        }
        return result;
    }

    /** merges to lists of strings, removing redundant entrys
     *
     * @param rList1 first list
     * @param rList2 secound list
     * @return result list
     */
    std::list<std::string> ListMerge(std::list<std::string> const& rList1, std::list<std::string> const& rList2)
    {
        std::list<std::string> tList1, tList2;
        tList1 = rList1;
        tList2 = rList2;
        tList1.sort();
        tList2.sort();
        tList1.merge(tList2);
        tList1.unique();
        return tList1;
    }


    /** prints a list to std::out, for debug only
     *
     * @param rList given list
     */
    void ListDebugPrint(std::list<std::string> rList)
    {
        std::list<std::string>::const_iterator it;
        std::cout << "###### DEBUG LIST PRINT #######" << std::endl;
        for (it = rList.begin(); it != rList.end(); it++)
        {
            std::cout << *it << std::endl;
        }
        std::cout << "###### DEBUG LIST PRINT END #######" << std::endl;
    }


    /** prints a list to std::out, for debug only
     *
     * @param rList given list
     */
    void ListDebugPrint(std::list<GenPropertyBase*> rList)
    {
        std::list<GenPropertyBase*>::const_iterator it;
        std::cout << "###### DEBUG LIST PRINT #######" << std::endl;
        for (it = rList.begin(); it != rList.end(); it++)
        {
            (*it)->ToOutStream(std::cout);
            std::cout << std::endl;
        }
        std::cout << "###### DEBUG LIST PRINT END #######" << std::endl;
    }


    /** extracts a key list from a list of properties
     *
     * @param rPropList given property list
     * @return list of keys as string
     */
    std::list<std::string> PropertyList2KeyList(std::list<GenPropertyBase*> rPropList)
    {
        std::list<std::string> result;
        std::list<GenPropertyBase*>::const_iterator it;

        for (it = rPropList.begin(); it != rPropList.end(); it++)
        {
            result.push_back((*it)->GetKey());
        }

        return result;
    }
}
