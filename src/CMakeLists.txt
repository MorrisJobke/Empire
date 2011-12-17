# project name
project(EMPIRE)

# may could be lower
cmake_minimum_required(VERSION 2.8)

# build tests?
set(ENABLE_TESTING ON)

# where to put executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wformat=2 -Winit-self -Winline -Wpacked -Wp,-D_FORTIFY_SOURCE=2 -Wpointer-arith -Wlarger-than-65500 -Wmissing-declarations -Wmissing-format-attribute -Wmissing-noreturn -Wredundant-decls -Wsign-compare -Wstrict-aliasing=2 -Wswitch-enum -Wundef -Wunreachable-code -Wunsafe-loop-optimizations -Wwrite-strings -Wuninitialized") #  -Weffc++



# adding sub directories
# parameter:
#   directory name
add_subdirectory(properties)
add_subdirectory(tests)

# specify executable
# parameter:
#   output name
#   source name
add_executable(Empire main2)

# link all together
# parameter
#   executable
#   used libraries
target_link_libraries(Empire PropertyInteger)