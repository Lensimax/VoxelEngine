set(PROJECT_NAME voxel-engine)

cmake_minimum_required(VERSION 2.8)


project(${PROJECT_NAME})



###### BUILD THIRDPARTY #######

# affectation des variables pour les includes
set(GLM_INCLUDE_DIR thirdparty/glm)
set(GLFW_INCLUDE_DIR thirdparty/glfw/include)
set(IMGUI_INCLUDE_DIR thirdparty/imgui)
set(GLAD_INCLUDE_DIR thirdparty/glad/include)
set(STB_IMAGE_DIR thirdparty/stb_image)
set(UTILITIES_DIR thirdparty/utilities)

# 3rd party libraries
add_subdirectory(thirdparty)

#find_package(glm)
#find_package(glfw)
#find_package(imgui)

# pour ajouter le fichier par défaut de ImGui
configure_file(data/default_imgui.ini imgui.ini  COPYONLY)


###### BUILD OPTION #######

add_definitions(-std=c++11 -pthread)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
add_definitions(-DGLFW_INCLUDE_NONE)

# BUILD TYPE = Debug | Release
if( NOT CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE Debug)
  message("BUILD TYPE = Debug | Release")
endif()


if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        message("DEBUG MODE ACTIVATED")

        add_definitions(-Wformat -Wall -g)

endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        message("RELEASE MODE ACTIVATED")

        add_definitions(-O3)

endif()

#### SET SOURCES ####


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






add_executable(${PROJECT_NAME} ${HEADERS} ${SRCS})

# ajout des includes directory
include_directories(
        ${GLM_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        ${GLAD_INCLUDE_DIR}
        ${IMGUI_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ${STB_IMAGE_DIR}
        ${UTILITIES_DIR}
)

target_link_libraries(${PROJECT_NAME} glfw glm glad imgui ${CMAKE_DL_LIBS})
