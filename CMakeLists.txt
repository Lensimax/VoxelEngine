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

# BUILD TYPE = Debug | Release
if( NOT CMAKE_BUILD_TYPE )
    set(CMAKE_BUILD_TYPE Debug)
    message("BUILD TYPE = Debug | Release")
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message("DEBUG MODE ACTIVATED")
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message("RELEASE MODE ACTIVATED")
endif()

add_definitions(-pthread )
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
add_definitions(-DGLFW_INCLUDE_NONE)


if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_definitions(-O3 -DNDEBUG)
endif()

# si le compilateur est Visual Studio
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    # Do Visual Studio specific stuff
else()
    add_definitions(-std=c++11)
    if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        add_definitions(-g)
        add_definitions(-Wformat -Wall -DDEBUG -Wdelete-non-virtual-dtor -Wshadow -Wextra -pedantic -fsanitize=address -fno-omit-frame-pointer)
        set(CMAKE_EXE_LINKER_FLAGS -fsanitize=address)
    endif()
    
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
