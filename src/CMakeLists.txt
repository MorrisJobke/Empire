PROJECT(EMPIRE)

ADD_LIBRARY(Property Property)
ADD_LIBRARY(PropertyInteger PropertyInteger)

ADD_EXECUTABLE(Empire main2)

TARGET_LINK_LIBRARIES(Empire PropertyInteger)