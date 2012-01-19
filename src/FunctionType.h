/* FunctionType.h
 * @Author:      kabum
 * @License:     GPL
 * @Created:     2012-01-18
 * @Editor:      Sublime Text 2
 */

#ifndef FUNCTIONTYPE_H
#define FUNCTIONTYPE_H

/** Lua Context
 */
class FunctionType
{
public:
    FunctionType();
    ~FunctionType();
    /** copy constructor
     */
    FunctionType(FunctionType& rOrigin);

    /** assignment operator
     */
    FunctionType& operator=(FunctionType& rRight);

    void ToOutStream(std::ostream& rOut);

    std::ostream& operator<<(std::ostream& lhs, FunctionType const& rhs);
};


#endif
