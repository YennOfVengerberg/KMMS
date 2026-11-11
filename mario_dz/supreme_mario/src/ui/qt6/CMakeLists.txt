find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_sources(${PROJECT_NAME}
	PRIVATE
		qt6_game_map.cpp
		qt6_ui_factory.cpp
		qt6_ui_obj_rect_adapter.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/ui_objects"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_compile_definitions(${PROJECT_NAME} PRIVATE
	QT6_SPRITE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/game_sprites"
)