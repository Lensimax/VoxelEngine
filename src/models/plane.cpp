#include "plane.h"

#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif


#include <iostream>



Plane::Plane(int id, std::string n, Transform *t, Material *m, MeshGrid *meshG) {
    transform = t;

    mesh = meshG;


    glm::vec3 center = mesh->getCenter();
    t->setCenter(center);

    createVAO();

    material = m;

    setName(n);
    setID(id);
}


Plane::~Plane(){
}
