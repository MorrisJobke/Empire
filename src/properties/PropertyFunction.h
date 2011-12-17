/* PropertyFunction.h
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-16.
 * @Editor:      Vim
 */

#ifndef PROPERTYINTEGER_H
#define PROPERTYINTEGER_H

#include "Property.cc"

#include <string>
using namespace std;

extern "C"
{
    #include "lua/lua.h"
}

class PropertyInteger : public Property<int>
{
private:
    string mMapFunction;
    string mReduceFunction;
    lua_State *myLuaState;

public:
    ~PropertyFunction();
    PropertyFunction(string const& key, string const& map, string const& reduce);

    void AddProperty(Property<T> property);
};

#endif
