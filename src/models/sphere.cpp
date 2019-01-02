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


#include "sphere.h"
#include "sphereMesh.h"


#include "../material/lambertian.h"



Sphere::Sphere(std::string n, float radius, unsigned int rings, unsigned int sectors, Transform *t, Material *m){
    setName(n);
    transform = t;

    mesh = new SphereMesh(radius, rings, sectors);

    material = m;

    createVAO();
}


Sphere::~Sphere(){
    deleteVAO();
    delete transform;
    delete material;
    delete mesh;
}

void Sphere::createUI(char *ID){
    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());
    ImGui::Separator();
    mesh->createUI();
    ImGui::Separator();

    transform->createUI();
    ImGui::Separator();
    material->createUI();
    ImGui::Separator();

    ImGui::EndChild();
}
