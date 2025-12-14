target_sources(menu
    PRIVATE 
        menu_functions.cpp
        menu_parts.cpp
        menu_functions.hpp
        menu_parts.hpp
        menu_struct.hpp   
)

target_include_directories(menu PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
)