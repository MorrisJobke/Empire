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
 *
 * @param rRight object to compare with
 *
 * @return boolean
 */
bool FunctionType::operator==(FunctionType& rRight)
{
    if (this->mList != rRight.mList)
        return false;

    return true;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** un-equal operator
 *
 * @param rRight object to compare with
 *
 * @return boolean
 */
bool FunctionType::operator!=(FunctionType& rRight)
{
    return not (*this == rRight);
}

/*============================= OPERATIONS =================================*/

/** overloaded operator to write class to stream
 *
 * wrappers ToOutStream
 *
 * @param rOut stream to write to
 * @param rFunctionType object to read from
 *
 * @return out stream
 */
std::ostream& operator<<(std::ostream& rOut, FunctionType rFunctionType)
{
    rFunctionType.ToOutStream(rOut);
    return rOut;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** overloaded operator to read class from stream
 *
 * doesn't work, because it isn't used in this way
 *
 * @param rIn stream to read from
 * @param rFunctionType object to write to
 *
 * @return in stream
 */
std::istream& operator>>(std::istream& rIn, FunctionType rFunctionType)
{
    return rIn;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** operator to write class to stream
 * @param rOut stream to write to
 */
void FunctionType::ToOutStream(std::ostream& rOut)
{
    rOut << "\nFunctionType";

    std::list<std::string>::iterator it;
    for (it = mList.begin(); it != mList.end(); it++) {
        rOut << "\t{" << *it << "}";
    }
}

/*============================= ACCESS     =================================*/

/** getter for first list entry (map function)
 *
 * @return std::string
 */
std::string FunctionType::GetMapFunction()
{
    std::list<std::string>::iterator it;
    it = mList.begin();
    if (it != mList.end())
        return *it;
    else
        return "";
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** getter for second list entry (reduce function)
 *
 * @return std::string
 */
std::string FunctionType::GetReduceFunction()
{
    std::list<std::string>::iterator it;
    it = mList.begin();
    it++;
    if (it != mList.end())
        return *it;
    else
        return "";
}

/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
