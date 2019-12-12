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


MeshRenderer::MeshRenderer() : m_material(NULL), m_showBoundingBox(false) {
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

    if(!m_material->getActive()){return;}

    glUseProgram(m_material->getShaderID());

    setUniform(modelMat, viewMat, projectionMat, light);

    Mesh *mesh = m_gameobject->getComponent<Mesh*>();
    if(mesh != NULL && mesh->getActive()){
        mesh->drawVAO();
    }

    glUseProgram(0);

    if(m_showBoundingBox){
        drawBoxWithMatrices(mesh->getMin()*1.1f, mesh->getMax()*1.1f, modelMat, viewMat, projectionMat);
    }

}

void MeshRenderer::createUI(){  
    ImGui::Text("Show bounding box : ");
    ImGui::SameLine(); ImGui::Checkbox("##showbounding", &m_showBoundingBox);  
}


void MeshRenderer::setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light){

    if(m_material == NULL){
        m_material = m_gameobject->getComponent<Material*>();
        if(m_material == NULL){return;}
    }
    assert(m_material != NULL);
    if(!m_material->getActive()){return;}
    
    // send the transformation matrix    
    m_material->callUniform(modelMat, viewMat, projectionMat, light);

}

void MeshRenderer::drawQuadWithTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4, float array[108], int i){
    /*glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v4.x, v4.y, v4.z);
    glVertex3f(v2.x, v2.y, v2.z);

    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v4.x, v4.y, v4.z);
    glVertex3f(v3.x, v3.y, v3.z);*/

    array[i] = v1.x; array[i+1] = v1.y; array[i+2] = v1.z;
    array[i+3] = v4.x; array[i+4] = v4.y; array[i+5] = v4.z;
    array[i+6] = v2.x; array[i+7] = v2.y; array[i+8] = v2.z;

    array[i+9] = v2.x; array[i+10] = v2.y; array[i+11] = v2.z;
    array[i+12] = v4.x; array[i+13] = v4.y; array[i+14] = v4.z;
    array[i+15] = v3.x; array[i+16] = v3.y; array[i+17] = v3.z;
}

// draw box that move with the object
void MeshRenderer::drawBoxWithMatrices(glm::vec3 min, glm::vec3 max, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat){
    Shader shader = Shader();
    shader.load("../data/shaders/displayBoundingBox.vert","../data/shaders/displayBoundingBox.frag");

    glUseProgram(shader.id());
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));


    float array[] = {
        min.x,max.y,max.z, min.x,min.y,max.z, max.x,max.y,max.z,
        max.x,max.y,max.z, min.x,min.y,max.z, max.x,min.y,max.z,
    };

    unsigned int nbVertices = 6;

    glLineWidth(1);
    DrawDebug::drawArrayPosition(nbVertices, array, GL_TRIANGLES, GL_LINE);
    
    glUseProgram(0);


}