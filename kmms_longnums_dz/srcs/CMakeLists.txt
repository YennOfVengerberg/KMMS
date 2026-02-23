target_sources(${library}
    PUBLIC
        long_nums.hpp
    PRIVATE 
        long_nums.cpp
)

target_include_directories(${library} PUBLIC "${PROJECT_SOURCE_DIR}/srcs")