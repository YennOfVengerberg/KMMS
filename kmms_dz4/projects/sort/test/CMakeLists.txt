set(SOURCES
    test_merge.cpp
)

add_executable(test_merge ${SOURCES})
target_link_libraries(test_merge
    gtest_main
    merge_sort_lib
)

add_test(test_merge test_merge.exe)