set(SOURCES
    test_merge.cpp
)

add_executable(test_merge ${SOURCES})
target_link_libraries(test_merge
    gtest_main
    ${library}
)

add_test(test_merge test_merge.exe)