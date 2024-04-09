set(SOURCES 
	test_sortings.cpp
)

add_executable(test_sortings ${SOURCES})
target_link_libraries(test_sortings 
	gtest_main 
	gmock_main 
	sortings_lib
)

add_test(test_sortings test_sortings)
