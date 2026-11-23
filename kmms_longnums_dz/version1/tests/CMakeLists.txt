set(SOURCES tests.cpp ) 
set(SOURCES_SEC test_long_number.cpp)

add_executable(tests ${SOURCES})
add_executable(tests_sec ${SOURCES_SEC})

target_link_libraries(tests
    ${library}
    gtest_main
    gmock_main
)

target_link_libraries(tests_sec
    ${library}
    gtest_main
    gmock_main
)

add_test(tests tests)
add_test(tests2 tests_sec)