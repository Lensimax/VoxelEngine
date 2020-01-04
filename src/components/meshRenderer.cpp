#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../models/mesh/mesh.h"

#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1
#define VERTEX_UV_ATTRIB 2


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <drawDebug.h>

#include <iostream>

#include "meshRenderer.h"

MeshRenderer::MeshRenderer() : m_showBoundingBox(false) {
    setName("Mesh Renderer");
}

void MeshRenderer::start() {
    mesh = m_gameobject->getComponent<Mesh*>();         assert(mesh != nullptr);
    material = m_gameobject->getComponent<Material*>(); assert(material != nullptr);
}

void MeshRenderer::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) {

    if(!material->getActive())
        return;

    glUseProgram(material->getShaderID());

    material->callUniform(modelMat, viewMat, projectionMat, light);

    if(mesh->getActive())
        mesh->drawVAO();

    glUseProgram(0);

    if(m_showBoundingBox)
        drawBoxWithMatrices(mesh->getMin()*1.1f, mesh->getMax()*1.1f, modelMat, viewMat, projectionMat);
}

void MeshRenderer::createUI(){  
    ImGui::Text("Show bounding box : "); ImGui::SameLine(); ImGui::Checkbox("##showbounding", &m_showBoundingBox);  
}

// draw box that move with the object
void MeshRenderer::drawBoxWithMatrices(glm::vec3 min, glm::vec3 max, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat){
    Shader shader = Shader();
    shader.load("../data/shaders/displayBoundingBox.vert","../data/shaders/displayBoundingBox.frag");

    glUseProgram(shader.id());
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));

    std::vector<glm::vec3> array;
    array.reserve(36);

    array.push_back(glm::vec3(min.x,max.y,max.z)); array.push_back(glm::vec3(min.x,min.y,max.z)); array.push_back(glm::vec3(max.x,max.y,max.z));
    array.push_back(glm::vec3(max.x,max.y,max.z)); array.push_back(glm::vec3(min.x,min.y,max.z)); array.push_back(glm::vec3(max.x,min.y,max.z));

    array.push_back(glm::vec3(max.x,max.y,min.z)); array.push_back(glm::vec3(max.x,min.y,min.z)); array.push_back(glm::vec3(min.x,max.y,min.z));
    array.push_back(glm::vec3(min.x,max.y,min.z)); array.push_back(glm::vec3(max.x,min.y,min.z)); array.push_back(glm::vec3(min.x,min.y,min.z));
    
    array.push_back(glm::vec3(min.x,max.y,min.z)); array.push_back(glm::vec3(min.x,min.y,min.z)); array.push_back(glm::vec3(min.x,min.y,max.z));
    array.push_back(glm::vec3(min.x,min.y,max.z)); array.push_back(glm::vec3(min.x,max.y,max.z)); array.push_back(glm::vec3(min.x,max.y,min.z));

    array.push_back(glm::vec3(max.x,max.y,max.z)); array.push_back(glm::vec3(max.x,min.y,max.z)); array.push_back(glm::vec3(max.x,max.y,min.z));
    array.push_back(glm::vec3(max.x,max.y,min.z)); array.push_back(glm::vec3(max.x,min.y,max.z)); array.push_back(glm::vec3(max.x,min.y,min.z));

    array.push_back(glm::vec3(min.x,min.y,max.z)); array.push_back(glm::vec3(min.x,min.y,min.z)); array.push_back(glm::vec3(max.x,min.y,max.z));
    array.push_back(glm::vec3(max.x,min.y,max.z)); array.push_back(glm::vec3(min.x,min.y,min.z)); array.push_back(glm::vec3(max.x,min.y,min.z));

    array.push_back(glm::vec3(min.x,max.y,min.z)); array.push_back(glm::vec3(min.x,max.y,max.z)); array.push_back(glm::vec3(max.x,max.y,min.z));
    array.push_back(glm::vec3(max.x,max.y,min.z)); array.push_back(glm::vec3(min.x,max.y,max.z)); array.push_back(glm::vec3(max.x,max.y,max.z));


    glLineWidth(1);
    DrawDebug::drawArrayPosition(array.size(), (float*)&(array[0]), GL_TRIANGLES, GL_LINE);
    
    glUseProgram(0);
}

