if(ENABLE_TESTING)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    find_package(Lua51 REQUIRED)
    # target_link_libraries(EmpireTest ${LUA_LIBRARIES})
    # if(LUA_FOUND)
    # ...
    # endif()

    # files to be included in executetable
    add_executable(EmpireTest
        MainTests
        FilesystemTests
        RepositoryTests
        GenPropertyTest)

    # used libraries
    target_link_libraries(EmpireTest
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${LUA_LIBRARIES}
        Filesystem
        GenProperty
        Repository)
endif()
