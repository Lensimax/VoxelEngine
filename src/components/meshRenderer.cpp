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

#include "meshRenderer.h"


void MeshRenderer::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){

    glUseProgram(m_material->getShaderID());

    setUniform(modelMat, viewMat, projectionMat, light);

    // TODO GETCOMPONENT
    //m_mesh->drawVAO();
    Mesh *mesh = m_gameobject->getComponent<Mesh*>();
    mesh->drawVAO();

    glUseProgram(0);

    // m_mesh->drawDebug(transform->getModelMat(),viewMat, projectionMat);



}



void MeshRenderer::setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light){

    // glm::mat4 model = transform->getMat4(modelMat);



    // send the transformation matrix
    m_material->callUniform(modelMat, viewMat, projectionMat, light);

}