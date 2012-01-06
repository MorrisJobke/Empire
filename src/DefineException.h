
/* DefineException.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-06.
 * @Editor:      Vim
 */

#ifndef DEFINEEXCEPTION_H
#define DEFINEEXCEPTION_H

#include <string>


/** this macro defines a standart exception
 */
#define DEFINE_FAST_EXCEPTION(className, Message) \
class className \
{ \
    private: \
        string mWhat; \
    public: \
        className() \
            : mWhat(Message) \
        { } \
        string what() \
        { \
            return mWhat; \
        } \
};




#endif
