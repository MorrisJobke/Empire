
/* ListHelper.h
 * @Author:      rbs (rbs@hrz.tu-chemnitz.de)
 * @License:     GPL
 * @Created:     2012-01-22
 * @Editor:      Sublime Text 2
 */

#ifndef LISTHELPER_H
#define LISTHELPER_H

#include <list>
#include <string>
#include <iostream>

#include "GenPropertyBase.h"

/** some functions for interacting with lists
 */
namespace ListHelper
{
    std::list<std::string> ListCompare(std::list<std::string> const& rList1, std::list<std::string> const& rList2, bool rNotFound);
    std::list<std::string> ListMerge(std::list<std::string> const& rList1, std::list<std::string> const& rList2);
    void ListDebugPrint(std::list<std::string> rList);
    std::list<std::string> PropertyList2KeyList(std::list<GenPropertyBase*> rPropList);
}

#endif
