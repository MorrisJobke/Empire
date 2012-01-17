
/* GenProperty.cpp
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2012-01-14.
 * @Editor:      Vim
 */

#include "GenPropertyNew.h"


/** define important types
 */
DEFINE_NEW_GETTYPENAME(int)
DEFINE_NEW_GETTYPENAME(int*)
DEFINE_NEW_GETTYPENAME(int&)
DEFINE_NEW_GETTYPENAME(float)
DEFINE_NEW_GETTYPENAME(float*)
DEFINE_NEW_GETTYPENAME(float&)
DEFINE_NEW_GETTYPENAME(double)
DEFINE_NEW_GETTYPENAME(double&)
DEFINE_NEW_GETTYPENAME(double*)
DEFINE_NEW_GETTYPENAME(std::string)
DEFINE_NEW_GETTYPENAME(std::string&)
DEFINE_NEW_GETTYPENAME(std::string*)



std::ostream& operator<<(std::ostream& rOut, GenPropertyBase& rProp)
{
   rProp.ToOutStream(rOut);
   return rOut;
};
