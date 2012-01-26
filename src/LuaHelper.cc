
/* LuaHelper.cc
 * @Author:      Brainafk
 * @License:     GPL
 * @Created:     2012-01-11.
 * @Editor:      Sublime Text 2
 */

#include "LuaHelper.h"

DEFINE_VAR_EXCEPTION(LuaException)

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
    std::string tmp = lua;
    std::size_t found;

    // LUA cause a SEGFAULT if the execution string is only "return ;"
    found = tmp.find("return");
    if (found != std::string::npos)
    {
        tmp.replace(found, found+6, "");
        found = tmp.find(";");
        while (found != std::string::npos)
        {
            tmp.replace(found, found+1, "");
            found = tmp.find(";");
        }

        bool alnum_found = false;
        std::string::iterator it;
        for (it=tmp.begin(); it < tmp.end(); it++)
        {
            if (isalnum(*it))
            {
                alnum_found = true;
                break;
            }
        }

        if (!alnum_found)
        {
            // throw LuaException("LUA string isn't valid");
            result = "0";
            return;
        }
    }

    // execution
    int ret = luaL_dostring(mState, (mVariables + lua).c_str());

    // raise exception if something fails
    if (ret != 0)
    {
        // throw LuaException("dostring error");
        result = "0";
        return;
    }

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
