
/* RegexHelper.h
 * @Author:      rbs (rbs@hrz.tu-chemnitz.de)
 * @License:     GPL
 * @Created:     2012-01-20.
 * @Editor:      Sublime Text 2
 */

#ifndef REGEXHELPER_H
#define REGEXHELPER_H

DEFINE_FAST_EXCEPTION(RegexExecuteError, "Regex execution failed")

#define INT_PATTERN "^[+-]?\\d+$"
#define FLOAT_PATTERN "^[+-]?((\\d+\\.\\d+)|\\.\\d+)$"
#define FUNCTION_PATTERN "^return.*;$"

#include <string>
#include <fstream>
#include <pcre.h>
#include <cstring>

/** some functions for auto recognition of types
 */
namespace RegexHelper
{
    bool MatchesRegex(std::string rTargetString, std::string rPattern);
    bool isInt(std::string value);
    bool isFloat(std::string value);
    bool isFunction(std::string value);
}

#endif
