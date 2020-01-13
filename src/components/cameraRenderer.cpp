

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
#include "cameraProjective.h"
#include "../material/shader.h"
 
CameraRenderer::CameraRenderer() : m_lineLength(0.2f), m_lineWidth(2.0f){
    setName("Camera Renderer");
}


CameraRenderer::~CameraRenderer(){

}



void CameraRenderer::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){

    CameraProjective * camera = m_gameobject->getComponent<CameraProjective*>();
    if(camera == NULL){
        return;
    }
    
    // GLMCOUT::printMat(modelMat);
    // GLMCOUT::printMat(viewMat);
    // std::cout << "\n\n";



    // const glm::vec3 forward = normalize(glm::vec3(inverted[2]));
    // glm::vec3 origin = m_gameobject->getTransform()->getPosition();
    glm::vec3 origin = glm::vec3(0, 0, 0);
    glm::vec3 forward = glm::vec3(0,0,1);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 right = glm::vec3(1, 0, 0);

    std::vector<glm::vec3> arrayAxis;


    glLineWidth(m_lineWidth);

    Shader shader = Shader();
    shader.load("../data/shaders/simple.vert","../data/shaders/simple.frag");
    glUseProgram(shader.id());
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    // glUniformMatrix4fv(glGetUniformLocation(shader.id(),"viewMat"),1,GL_FALSE,&(glm::mat4(1.0f)[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));
    
    // Z axis
    glm::vec4 color = glm::vec4(0,0,1,1);
    glUniform4fv(glGetUniformLocation(shader.id(),"color"), 1, &color[0]);
    arrayAxis.resize(2);
    arrayAxis[0] = origin; arrayAxis[1] = forward*m_lineLength;
    DrawDebug::drawArrayPosition(arrayAxis.size(), (float*)&arrayAxis[0], GL_LINES);

    // Y axis
    color = glm::vec4(0,1,0,1);
    glUniform4fv(glGetUniformLocation(shader.id(),"color"), 1, &color[0]);
    arrayAxis.resize(2);
    arrayAxis[0] = origin; arrayAxis[1] = up*m_lineLength;
    DrawDebug::drawArrayPosition(arrayAxis.size(), (float*)&arrayAxis[0], GL_LINES);

    // X axis
    color = glm::vec4(1,0,0,1);
    glUniform4fv(glGetUniformLocation(shader.id(),"color"), 1, &color[0]);
    arrayAxis.resize(2);
    arrayAxis[0] = origin; arrayAxis[1] = right*m_lineLength;
    DrawDebug::drawArrayPosition(arrayAxis.size(), (float*)&arrayAxis[0], GL_LINES);

    glUseProgram(0);
}


void CameraRenderer::createUI(){
    ImGui::Text("Line length : ");
    ImGui::DragFloat("##lineLength", &m_lineLength, 0.01f,0.01f, 1000.f); 
    ImGui::Text("Line width : ");
    ImGui::DragFloat("##linewidth", &m_lineWidth,0.2f, 1.0f, 1000.0f); 
}