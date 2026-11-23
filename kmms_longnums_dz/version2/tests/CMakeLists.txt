set(SOURCES tests.cpp)
set(SOURCES_SEC test_long_number.cpp)
set(SOURCES_MATH test_math_upgrade.cpp)

add_executable(tests ${SOURCES})
add_executable(tests_sec ${SOURCES_SEC})
add_executable(tests_math ${SOURCES_MATH})

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

target_link_libraries(tests_math
    ${library}
    gtest_main
    gmock_main
)

add_test(tests tests)
add_test(tests2 tests_sec)
add_test(tests_math tests_math)
