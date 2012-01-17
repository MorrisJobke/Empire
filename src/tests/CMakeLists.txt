if(ENABLE_TESTING)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)

    # files to be included in executetable
    add_executable(EmpireTest
        MainTests
        FilesystemTests
        RepositoryTests
        CommandTests
        #GenPropertyTest
        TemplateTests)

    # used libraries
    target_link_libraries(EmpireTest
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        Filesystem
        #GenProperty
        GenPropertyNew
        Repository
        Template)
endif()
