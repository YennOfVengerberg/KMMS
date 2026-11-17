target_sources(${PROJECT_NAME}
	PRIVATE
		game.cpp
		runtime_factory.cpp
)

if(GAME_TYPE STREQUAL "Qt6")
	target_sources(${PROJECT_NAME} PRIVATE qt6_runtime.cpp)
else()
	target_sources(${PROJECT_NAME} PRIVATE console_runtime.cpp)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)
