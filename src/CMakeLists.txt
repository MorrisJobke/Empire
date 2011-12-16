# project name
project(EMPIRE)

# may could be lower
cmake_minimum_required(VERSION 2.8)

# adding sub directories
# parameter:
#   directory name
add_subdirectory(properties)

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