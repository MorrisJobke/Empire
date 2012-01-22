
/* LuaHelper.cc
 * @Author:      Brainafk
 * @License:     GPL
 * @Created:     2012-01-11.
 * @Editor:      Sublime Text 2
 */

#include "LuaHelper.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/** LuaHelper's Constructor
 */
LuaHelper::LuaHelper()
{
    mState = lua_open();
}

/** LuaHelper's Destructor
 */
LuaHelper::~LuaHelper()
{
    lua_close(mState);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** LuaContext's Constructor
 *
 * @param state a lua state needed to execute LUA script code
 */
LuaContext::LuaContext(lua_State* state)
:   mState(state),
    mVariables("")
{
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** LuaHelper's Destructor
 */
LuaContext::~LuaContext()
{
}

/*============================= OPERATORS ==================================*/
/*============================= OPERATIONS =================================*/

/** create and return a new LuaContext
 *
 * @return a new LuaContext
 */
LuaContext* LuaHelper::CreateContext()
{
    return new LuaContext(mState);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** add variable of type int
 *
 * @param name the variable name
 * @param value variable name
 */
void LuaContext::AddVariable(std::string const& name, int value)
{
    std::ostringstream oss;
    oss << name << "=" << value << ";";
    mVariables += oss.str();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** add variable of type double
 *
 * @param name variable name
 * @param value variable name
 */
void LuaContext::AddVariable(std::string const& name, double value)
{
    std::ostringstream oss;
    oss << name << "=" << value << ";";
    mVariables += oss.str();
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** execute given lua script
 *
 * @param lua script to execute
 * @param result value for storing the execution result
 */
void LuaContext::Execute(std::string const& lua, std::string& result)
{
    luaL_dostring(mState, (mVariables + lua).c_str());

    result = lua_tostring(mState, -1);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/** execute given lua script
 *
 * @param lua script to execute
 * @param result value for storing the execution result
 */
void LuaContext::Execute(std::string const& lua, double& result)
{
    std::string str_result;
    Execute(lua, str_result);

    std::istringstream i(str_result);
    i >> result;
}

/*============================= ACCESS     =================================*/
/*============================= INQUIRY    =================================*/

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
