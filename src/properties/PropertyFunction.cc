/* PropertyFunction.cc
 * @Author:       ()
 * @License:     GPL
 * @Created:     2011-12-17.
 * @Editor:      Vim
 */

#include "PropertyFunction.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

PropertyFunction::PropertyFunction(string const& key, string const& map, string const& reduce)
: mMapFunction(map), mReduceFunction(reduce), myLuaState(lua_open())
{
    Init(key);
}

/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/

void
PropertyFunction::AddProperty(Property property)
{
    // register global lua variable
}

/*============================= ACESS      =================================*/
// template<class T> T
// Property<T>::GetValue() new
// {
//     // luaL_dostring(L, "return 'somestring'");
//     // const char * str = lua_tostring(L, -1);
// }

// template<class T> void new
// Property<T>::SetValue(T value)
// {
// }

/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
