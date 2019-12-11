
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

#include "cameraRenderer.h"

#include <iostream>

CameraRenderer::CameraRenderer(){
    setName("Camera Renderer");
}


CameraRenderer::~CameraRenderer(){

}

void CameraRenderer::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){
    std::cout << "PAsse ici\n";
    

    /*glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0,0,0);
    glVertex3f(0.2, 0.5, 0);
    glVertex3f(1, 0.5, 0);
    glEnd();*/

    Shader *shader = new Shader();
    shader->load("../data/shaders/displayBoundingBox.vert","../data/shaders/displayBoundingBox.frag");

    glUseProgram(shader->id());

    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glLineWidth(2);
    glBegin(GL_TRIANGLES);

    glVertex3f(-0.5, 0, 0);
    glVertex3f(0.5, 0, 0);
    glVertex3f(0.5, 0, 0.5);

    glVertex3f(-0.5, 1, 0);
    glVertex3f(0.5, 1, 0);
    glVertex3f(0.5, 1, 0.5);

    glEnd();

    glUseProgram(0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    delete shader;

}

void CameraRenderer::createUI(){

    ImGui::Text("Line length : ");
    ImGui::DragFloat("##lineLength", &m_lineLength, 0.01f,0.01f, 1000.f); 

}