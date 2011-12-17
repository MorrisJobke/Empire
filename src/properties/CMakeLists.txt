# adding libraries
# parameter:
#	library cmake name
#	source name
add_library(Property Property)
add_library(PropertyInteger PropertyInteger)
add_library(PropertyFloat PropertyFloat)
add_library(PropertyString PropertyString)
add_library(PropertyFunction PropertyFunction)

if(NOT LUA_FOUND)
    # used by PropertyFunction
    find_package(Lua51 REQUIRED)
endif()
