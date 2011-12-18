/* PropertyFunction.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#ifndef PROPERTYFUNCTION_H
#define PROPERTYFUNCTION_H

#ifndef PROPERTY_H
#   include "Property.cc"
#endif

#include <string>
using namespace std;

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class PropertyFunction : public Property<int>
{
private:
    string mMapFunction;
    string mReduceFunction;
    lua_State *myLuaState;

public:
    ~PropertyFunction();
    PropertyFunction(string const& key, string const& map, string const& reduce);

    template<class T> void AddProperty(Property<T> property);
};

#endif
