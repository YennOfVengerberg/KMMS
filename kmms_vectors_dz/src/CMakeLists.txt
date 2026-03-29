target_sources(${CONTAINERS_LIB} 
	PRIVATE
		doubly_linked_list.cpp
		vector.cpp
	PUBLIC
		doubly_linked_list.hpp
		vector.hpp
)

target_include_directories(${CONTAINERS_LIB} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)
