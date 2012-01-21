
/* RegexHelper.h
 * @Author:      rbs (rbs@hrz.tu-chemnitz.de)
 * @License:     GPL
 * @Created:     2012-01-20.
 * @Editor:      Sublime Text 2
 */

#ifndef REGEXHELPER_H
#define REGEXHELPER_H

#define INT_PATTERN "^[+-]?\\d+$"
#define FLOAT_PATTERN "^[+-]?((\\d+\\.\\d+)|\\.\\d+)$"

#include <string>
#include <fstream>
#include <pcre.h>
#include <cstring>

namespace RegexHelper
{
    bool MatchesRegex(std::string rTargetString, std::string rPattern);
    bool isInt(std::string value);
    bool isFloat(std::string value);
}

#endif
