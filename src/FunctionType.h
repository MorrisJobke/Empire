/* FunctionType.h
 * @Author:      kabum
 * @License:     GPL
 * @Created:     2012-01-18
 * @Editor:      Sublime Text 2
 */

#ifndef FUNCTIONTYPE_H
#define FUNCTIONTYPE_H

#include <list>
#include <string>
#include <iostream>

/** data type for our so-called "functions"
 */
class FunctionType
{
private:
    std::list<std::string> mList;
public:
    FunctionType();
    FunctionType(std::list<std::string> const& rFunctions);

    bool operator==(FunctionType& rRight);
    bool operator!=(FunctionType& rRight);

    void ToOutStream(std::ostream& rOut);
};


std::ostream& operator<<(std::ostream& rOut, FunctionType rFunctionType);
std::istream& operator>>(std::istream& rIn, FunctionType rFunctionType);


#endif
