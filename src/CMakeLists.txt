# project name
project(EMPIRE)

# may could be lower
cmake_minimum_required(VERSION 2.8)

# build tests?
set(ENABLE_TESTING ON)

# where to put executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

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