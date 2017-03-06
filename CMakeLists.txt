cmake_minimum_required(VERSION 2.8.1)

function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)

set(PROJECT_NAME "engine")
set(DEMO_NAME "demo")

set_property(GLOBAL PROPERTY USE)

find_package(OpenGL REQUIRED)

# TODO: Linux / Mac ??
if (WIN32)
	set(LIB_INCLUDE "${CMAKE_SOURCE_DIR}/lib/include")
	set(LIB_LIBRARIES "${CMAKE_SOURCE_DIR}/lib/lib")
	set(LIB_BINARIES "${CMAKE_SOURCE_DIR}/lib/bin")
	set(ENGINE_INCLUDE "${CMAKE_SOURCE_DIR}/engine")
endif()

project(${PROJECT_NAME})

include_directories( ${LIB_INCLUDE} ${ENGINE_INCLUDE} )
link_directories( ${LIB_LIBRARIES} )

FILE(GLOB_RECURSE ENGINE_SOURCES engine/*)
FILE(GLOB_RECURSE DEMO_SOURCES demo/*)

assign_source_group(${ENGINE_SOURCES})
assign_source_group(${DEMO_SOURCES})

add_library( ${PROJECT_NAME} ${ENGINE_SOURCES} )
add_executable( ${DEMO_NAME} ${DEMO_SOURCES} )

target_link_libraries(
	${PROJECT_NAME}
	opengl32
	glew32s
	glfw3
	assimp-vc140-mt
)

target_link_libraries(
	${DEMO_NAME}
	${PROJECT_NAME}
)

if (WIN32)

	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${LIB_BINARIES}/glfw3.dll"
		"${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>"
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${LIB_BINARIES}/assimp-vc140-mt.dll"
		"${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>"
	)

endif()