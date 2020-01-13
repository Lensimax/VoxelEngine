

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

    if(!getActive()){
        return;
    }

    CameraProjective * camera = m_gameobject->getComponent<CameraProjective*>();
    if(camera == NULL){
        return;
    }


    // pour enlever la rotation sur la matrix model
    modelMat[0][0] = 1; modelMat[1][1] = 1; modelMat[2][2] = 1; 
    modelMat[0][1] = 0; modelMat[0][2] = 0;
    modelMat[1][0] = 0; modelMat[1][2] = 0;
    modelMat[2][0] = 0; modelMat[2][1] = 0;

    std::vector<glm::vec3> arrayAxis;


    glLineWidth(0.5f);

    Shader shader = Shader();
    shader.load("../data/shaders/simple.vert","../data/shaders/simple.frag");
    glUseProgram(shader.id());
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));
    
    // Z axis
    glm::vec4 color = glm::vec4(1,0,0,1);
    glUniform4fv(glGetUniformLocation(shader.id(),"color"), 1, &color[0]);

    const float size = 0.2f;

    // face dessus
    arrayAxis.push_back(glm::vec3(-size, size, size));
    arrayAxis.push_back(glm::vec3(size, size, size));
    arrayAxis.push_back(glm::vec3(size, size, size));
    arrayAxis.push_back(glm::vec3(size, size, -size));
    arrayAxis.push_back(glm::vec3(size, size, -size));
    arrayAxis.push_back(glm::vec3(-size, size, -size));
    arrayAxis.push_back(glm::vec3(-size, size, -size));
    arrayAxis.push_back(glm::vec3(-size, size, size));
    // face dessus
    arrayAxis.push_back(glm::vec3(-size, -size, size));
    arrayAxis.push_back(glm::vec3(size, -size, size));
    arrayAxis.push_back(glm::vec3(size, -size, size));
    arrayAxis.push_back(glm::vec3(size, -size, -size));
    arrayAxis.push_back(glm::vec3(size, -size, -size));
    arrayAxis.push_back(glm::vec3(-size, -size, -size));
    arrayAxis.push_back(glm::vec3(-size, -size, -size));
    arrayAxis.push_back(glm::vec3(-size, -size, size));

    arrayAxis.push_back(glm::vec3(-size, size, -size));
    arrayAxis.push_back(glm::vec3(-size, -size, -size));
    arrayAxis.push_back(glm::vec3(size, size, -size));
    arrayAxis.push_back(glm::vec3(size, -size, -size));
    arrayAxis.push_back(glm::vec3(-size, size, size));
    arrayAxis.push_back(glm::vec3(-size, -size, size));
    arrayAxis.push_back(glm::vec3(size, size, size));
    arrayAxis.push_back(glm::vec3(size, -size, size));


    DrawDebug::drawArrayPosition(arrayAxis.size(), (float*)&arrayAxis[0], GL_LINES);

    glUseProgram(0);
}


void CameraRenderer::createUI(){
    ImGui::Text("Line length : ");
    ImGui::DragFloat("##lineLength", &m_lineLength, 0.01f,0.01f, 1000.f); 
    ImGui::Text("Line width : ");
    ImGui::DragFloat("##linewidth", &m_lineWidth,0.2f, 1.0f, 1000.0f); 
}