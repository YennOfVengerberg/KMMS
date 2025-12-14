target_sources(merge_sort
    PRIVATE 
        io.cpp
        io.hpp
        sort.cpp
        sort.hpp
)

target_include_directories(merge_sort PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
)