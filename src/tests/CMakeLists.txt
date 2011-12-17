if(ENABLE_TESTING)
	find_package(Boost COMPONENTS unit_test_framework REQUIRED)

	add_executable(EmpireTest
		MainTests
		PropertyIntegerTests
		PropertyFloatTests
    PropertyFunctionTests)

	target_link_libraries(EmpireTest
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
		PropertyInteger
		PropertyFloat
    PropertyFunction)
endif()