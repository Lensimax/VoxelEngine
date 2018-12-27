
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


#include "cube.h"

#include <iostream>

#include "../material/lambertian.h"


Cube::Cube(std::string n, Transform *t, Material *m){
    transform = t;

    mesh = new CubeMesh();


    float *center = mesh->getCenter();
    t->setCenter(glm::vec3(center[0],center[1], center[2]));

    createVAO();

    material = m;

    name = n;
}


Cube::~Cube(){
    deleteVAO();
    delete transform;
    delete material;
    delete mesh;
}
