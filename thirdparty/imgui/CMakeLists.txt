

file(GLOB_RECURSE SRCS_IMGUI
	*.cpp
	*.c
)


file(GLOB_RECURSE HEADERS_IMGUI
	*.h
	*.hpp
)

add_definitions( -ldl )

add_library(imgui STATIC ${SRCS_IMGUI} ${HEADERS_IMGUI} )
