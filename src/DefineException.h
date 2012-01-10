
/* DefineException.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-06.
 * @Editor:      Vim
 */

#ifndef DEFINEEXCEPTION_H
#define DEFINEEXCEPTION_H

#include <string>


/** this macro defines a standard exception
 */
#define DEFINE_FAST_EXCEPTION(className, Message) \
class className \
{ \
    private: \
        std::string mWhat; \
    public: \
        className() \
            : mWhat(Message) \
        { } \
        std::string what() \
        { \
            return mWhat; \
        } \
};


/** this macro defines a standard exception
 */
#define DEFINE_VAR_EXCEPTION(className) \
class className \
{ \
    private: \
        std::string mWhat; \
    public: \
        className(std::string const& message) \
            : mWhat(message) \
        { } \
        std::string what() \
        { \
            return mWhat; \
        } \
};


#endif
