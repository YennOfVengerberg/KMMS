target_sources(${library}
    PRIVATE 
        
    PUBLIC
        io.hpp
        sort.hpp
        io.cpp
        sort.cpp
)

target_include_directories(${library} PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
)
