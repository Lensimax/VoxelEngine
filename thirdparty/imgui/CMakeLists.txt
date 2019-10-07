

file(GLOB_RECURSE SRCS_IMGUI
	*.cpp
	*.c
)


file(GLOB_RECURSE HEADERS_IMGUI
	*.h
	*.hpp
)

include_directories(
        ${GLFW_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
)


add_definitions( -ldl )
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

add_library(imgui STATIC ${SRCS_IMGUI} ${HEADERS_IMGUI} )

target_link_libraries (imgui glfw glad ${OPENGL_LIBRARIES})

set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
