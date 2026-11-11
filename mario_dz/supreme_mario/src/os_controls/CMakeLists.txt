add_subdirectory(os_api)

if(GAME_TYPE STREQUAL "WindowsConsole")
    add_subdirectory(windows)
elseif(GAME_TYPE STREQUAL "LinuxConsole")
    add_subdirectory(linux)
elseif(GAME_TYPE STREQUAL "Qt6")
    add_subdirectory(qt6)
endif()
