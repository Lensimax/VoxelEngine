#include "plane.h"

#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


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



Plane::Plane(int id, std::string n, unsigned int size, float width, float gridZ, Transform *t, Material *m) {
    transform = t;

    mesh = new MeshGrid(size, width, gridZ);


    glm::vec3 center = mesh->getCenter();
    t->setCenter(center);

    createVAO();

    material = m;

    setName(n);
    setID(id);
}


Plane::~Plane(){
    deleteVAO();
    delete material;
    delete mesh;
    
}
