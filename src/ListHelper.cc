
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
     * @param rList1 secound list
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
}
