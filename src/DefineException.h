
/* DefineException.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-06.
 * @Editor:      Vim
 */

#ifndef DEFINEEXCEPTION_H
#define DEFINEEXCEPTION_H

#include <string>
#include <stdexcept>

/** base exception class to avoid redeclaration of what()
 */
class BaseException : public std::runtime_error {
public:
    std::string mWhat; ///< store message
    /** the constructor
     *
     * @param message error message
     */
    BaseException(std::string const message)
        : std::runtime_error(message) {};
    /** what message is stored
     *
     * @return error message
     */
    std::string what()
    {
        return mWhat;
    }
    ~BaseException() throw() {};
};

/** this macro defines a standard exception
 */
#define DEFINE_FAST_EXCEPTION(className, Message) \
class className : public BaseException\
{ \
    public: \
        className() \
            : BaseException(Message) \
        { } \
};


/** this macro defines a standard exception
 */
#define DEFINE_VAR_EXCEPTION(className) \
class className : public BaseException \
{ \
    public: \
        className(std::string const& message) \
            : BaseException(message) \
        { } \
};


#endif
