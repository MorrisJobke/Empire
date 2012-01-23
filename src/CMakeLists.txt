# project name
project(EMPIRE)

# may could be lower
cmake_minimum_required(VERSION 2.8)

# build tests?
set(ENABLE_TESTING ON)

# where to put executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

#
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wformat=2 -Winit-self -Winline -Wpacked -Wp,-D_FORTIFY_SOURCE=2 -Wpointer-arith -Wlarger-than-65500 -Wmissing-declarations -Wmissing-format-attribute -Wmissing-noreturn -Wredundant-decls -Wsign-compare -Wstrict-aliasing=2 -Wswitch-enum -Wundef -Wunreachable-code -Wunsafe-loop-optimizations -Wwrite-strings -Wuninitialized")

find_package(Lua51 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
# find_package(PCRE REQUIRED) // still not distributed
include(${PROJECT_BINARY_DIR}/../src/FindPCRE.cmake)
if(NOT PCRE_FOUND)
    message(FATAL_ERROR "PCRE not installed, CMake will exit.")
endif()

# some annoying warnings: (disabled in above Code)
# -Weffc++

# libraries

######################
# Filesystem library #
######################
add_library(Filesystem Filesystem)

########################
# SyntaxParser library #
########################
add_library(SyntaxParser SyntaxParser)

#######################
# RegexHelper library #
#######################
add_library(RegexHelper RegexHelper)
target_link_libraries(RegexHelper
    ${PCRE_LIBRARIES})

########################
# FunctionType library #
########################
add_library(FunctionType FunctionType)
target_link_libraries(FunctionType
    LuaHelper)

#######################
# GenProperty library #
#######################
add_library(GenProperty GenProperty)
target_link_libraries(GenProperty
    FunctionType)

######################
# Repository library #
######################
add_library(Repository Repository)
target_link_libraries(Repository
    Filesystem
    GenProperty
    RegexHelper)

######################
# Lua Helper library #
######################
add_library(LuaHelper LuaHelper)
target_link_libraries(LuaHelper
    ${LUA_LIBRARIES})

######################
# Template library   #
######################
add_library(Template Template)
target_link_libraries(Template
    GenProperty
    LuaHelper
    FunctionType)

######################
# Collection library   #
######################
add_library(Collection Collection)
target_link_libraries(Collection
    Filesystem
    GenProperty)

# adding sub directories
# parameter:
#   directory name
add_subdirectory(tests)

# specify executable
# parameter:
#   output name
#   source name
add_executable(Empire Empire)

# link all together
# parameter
#   executable
#   used libraries
target_link_libraries(Empire
    Repository
    SyntaxParser
    Filesystem)
