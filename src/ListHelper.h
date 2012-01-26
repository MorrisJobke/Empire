
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

namespace ListHelper
{
    std::list<std::string> ListCompare(std::list<std::string> const& rList1, std::list<std::string> const& rList2, bool rNotFound);
}

#endif
