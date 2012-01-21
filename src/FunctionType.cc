/* FunctionType.cc
 * @Author:      kabum
 * @License:     GPL
 * @Created:     2012-01-18
 * @Editor:      Sublime Text 2
 */

#include "FunctionType.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/** the constructor
 */
FunctionType::FunctionType()
{
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** the constructor
 *
 * @param rFunctions list of strings with functions
 */
FunctionType::FunctionType(std::list<std::string> const& rFunctions)
:   mList(rFunctions)
{
}

/*============================= OPERATORS ==================================*/

/** equal operator
 */
bool FunctionType::operator==(FunctionType& rRight)
{
    if (this->mList != rRight.mList)
        return false;

    return true;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** un-equal operator
 */
bool FunctionType::operator!=(FunctionType& rRight)
{
    return not (*this == rRight);
}

/*============================= OPERATIONS =================================*/

/** overloaded operator to write class to stream
 *
 * wrappers ToOutStream
 */
std::ostream& operator<<(std::ostream& rOut, FunctionType rFunctionType)
{
    rFunctionType.ToOutStream(rOut);
    return rOut;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** overloaded operator to read class from stream
 */
std::istream& operator>>(std::istream& rIn, FunctionType rFunctionType)
{
    return rIn;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** operator to write class to stream
 */
void FunctionType::ToOutStream(std::ostream& rOut)
{
    rOut << "huhu";
}

/*============================= ACCESS     =================================*/
/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
