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

#include <iostream>

#include "meshRenderer.h"


MeshRenderer::MeshRenderer() : m_material(NULL) {
    setName("Mesh Renderer");
}

MeshRenderer::~MeshRenderer(){

}


void MeshRenderer::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){

    if(m_material == NULL){
        m_material = m_gameobject->getComponent<Material*>();
        if(m_material == NULL){return;}
    }

    assert(m_material != NULL);

    glUseProgram(m_material->getShaderID());

    setUniform(modelMat, viewMat, projectionMat, light);

    Mesh *mesh = m_gameobject->getComponent<Mesh*>();
    if(mesh != NULL){
        mesh->drawVAO();
    }

    glUseProgram(0);

}

void MeshRenderer::createUI(){    
}


void MeshRenderer::setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light){

    if(m_material == NULL){
        m_material = m_gameobject->getComponent<Material*>();
        if(m_material == NULL){return;}
    }
    assert(m_material != NULL);
    // send the transformation matrix
    m_material->callUniform(modelMat, viewMat, projectionMat, light);

}