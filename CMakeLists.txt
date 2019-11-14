set(PROJECT_NAME green-engine)


project(${PROJECT_NAME})


cmake_minimum_required(VERSION 2.8)


# affectation des variables pour les includes
set(GLM_INCLUDE_DIR thirdparty/glm)
set(GLFW_INCLUDE_DIR thirdparty/glfw/include)
set(IMGUI_INCLUDE_DIR thirdparty/imgui)
set(GLAD_INCLUDE_DIR thirdparty/glad/include)
set(STB_IMAGE_DIR thirdparty/stb_image)

# 3rd party libraries
add_subdirectory(thirdparty)

#find_package(glm)
#find_package(glfw)
#find_package(imgui)

# pour ajouter le fichier par défaut de ImGui
configure_file(data/default_imgui.ini imgui.ini  COPYONLY)



# SRCS prends la valeur des sources
file(GLOB_RECURSE SRCS
	src/*.c
	src/*.cpp
)

# SRCS prends la valeur des headers
file(GLOB_RECURSE HEADERS
	src/*.h
	src/*.hpp
)

add_definitions( -ldl -Wformat -Wall)
add_definitions(-std=c++11)


add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
add_definitions(-DGLFW_INCLUDE_NONE)




add_executable(${PROJECT_NAME} ${HEADERS} ${SRCS})

# ajout des includes directory
include_directories(
        ${GLM_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIR}
        ${IMGUI_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${STB_IMAGE_DIR}
)

target_link_libraries(${PROJECT_NAME} glfw glm glad imgui ${CMAKE_DL_LIBS})
