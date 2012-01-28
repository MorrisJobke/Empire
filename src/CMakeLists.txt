# project name
project(EMPIRE)

# may could be lower
cmake_minimum_required(VERSION 2.8)

# build tests?
set(ENABLE_TESTING ON)
set(ONLY_TESTING OFF)

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

######################
# ListHelper library #
######################
add_library(ListHelper ListHelper)

########################
# SyntaxParser library #
########################
add_library(SyntaxParser SyntaxParser)
target_link_libraries(SyntaxParser
    Repository
    Template
    Filesystem
    Collection
    ListHelper
    RegexHelper)

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

#######################
# GenProperty library #
#######################
add_library(GenProperty GenProperty)
target_link_libraries(GenProperty
    Collection
    FunctionType)

######################
# Repository library #
######################
add_library(Repository Repository)
target_link_libraries(Repository
    Filesystem
    GenProperty
    RegexHelper
    ListHelper)

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
    FunctionType
    ListHelper
    Filesystem)

######################
# Collection library #
######################
add_library(Collection Collection)
target_link_libraries(Collection
    Filesystem
    GenProperty)

# adding sub directories
# parameter:
#   directory name
add_subdirectory(tests)

if(NOT ONLY_TESTING)
    # specify executable
    # parameter:
    #   output name
    #   source name
    add_executable(emp Empire)

    # link all together
    # parameter
    #   executable
    #   used libraries
    target_link_libraries(emp
        Repository
        SyntaxParser)
endif()


#
# installing
#
message("prefix: ${CMAKE_INSTALL_PREFIX}")
message("bindir: ${CMAKE_CURRENT_BINARY_DIR}")

INSTALL(PROGRAMS ../bin/emp DESTINATION bin)

