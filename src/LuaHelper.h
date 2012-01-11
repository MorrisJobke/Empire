
/* LuaHelper.h
 * @Author:      Brainafk
 * @License:     GPL
 * @Created:     2012-01-11.
 * @Editor:      Sublime Text 2
 */

#ifndef LUAHELPER_H
#define LUAHELPER_H

#include <string>
#include <sstream>

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

/** Lua Context
 */
class LuaContext
{
private:
    lua_State *mState;
    std::string mVariables;

public:
    LuaContext(lua_State* state);
    ~LuaContext();

    void AddVariable(std::string const& name, int& value);
    void AddVariable(std::string const& name, double& value);

    void Execute(std::string const& lua, std::string& result);
    void Execute(std::string const& lua, double& result);
};

/** Helper Class for Lua related stuff
 */
class LuaHelper
{
private:
    lua_State *mState;

public:
    LuaHelper();
    ~LuaHelper();

    LuaContext* CreateContext();
};

#endif
