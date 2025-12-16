target_sources(merge_sort_lib
    PRIVATE 
        
    PUBLIC
        io.hpp
        sort.hpp
        io.cpp
        sort.cpp
)

target_include_directories(merge_sort_lib PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
)
