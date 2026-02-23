set(SOURCES tests.cpp)

add_executable(tests ${SOURCES})

target_link_libraries(tests
    ${library}
    gtest_main
    gmock_main
)

add_test(tests tests)