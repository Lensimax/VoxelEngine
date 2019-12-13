
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <drawDebug.h>
#include <glmCout.h>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "cameraRenderer.h"

#include "../models/mesh/meshCube.h"

#include <iostream>

CameraRenderer::CameraRenderer() : m_cam(NULL){
    setName("Camera Renderer");
}


CameraRenderer::~CameraRenderer(){

}

void CameraRenderer::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){
    Camera* cam;
    
    if(m_cam == NULL){
        if(cam = dynamic_cast<Camera*>(m_gameobject)) {
            m_cam = cam;
        }
    }

    if(m_cam == NULL){
        return;
    }
    glm::vec3 pos = m_cam->getPosition();

    glm::mat4 mat = glm::translate(m_cam->getModel(), m_cam->getPosition());

    glm::vec4 origin = mat*glm::vec4(0, 0, 0, 1.0);

    glm::vec4 forward = origin + vec4(1,0,0,0);

    GLMCOUT::printVec(origin);

    float arrayCam[] = {
        origin.x,origin.y,origin.z,
        forward.x,forward.y,forward.z
    };


    glm::vec4 color = glm::vec4(1,0,0,1);
    Shader shader = Shader();
    shader.load("../data/shaders/simple.vert","../data/shaders/simple.frag");

    glUseProgram(shader.id());

    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));
    

    glUniform4fv(glGetUniformLocation(shader.id(),"color"), 1, &color[0]);

    glLineWidth(2);
    DrawDebug::drawArrayPosition(2, arrayCam, GL_LINES);

    glUseProgram(0);


}

void CameraRenderer::createUI(){

    ImGui::Text("Line length : ");
    ImGui::DragFloat("##lineLength", &m_lineLength, 0.01f,0.01f, 1000.f); 

}