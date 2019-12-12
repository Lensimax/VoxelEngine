
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm_display.h>

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

CameraRenderer::CameraRenderer(){
    setName("Camera Renderer");
}


CameraRenderer::~CameraRenderer(){

}

void CameraRenderer::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){
    

    /*glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0,0,0);
    glVertex3f(0.2, 0.5, 0);
    glVertex3f(1, 0.5, 0);
    glEnd();*/

    glm::vec4 color = glm::vec4(0,1,0,1);

    Mesh *mesh = new MeshCube(0.1f);

    Shader *shader = new Shader();
    shader->load("../data/shaders/simple.vert","../data/shaders/simple.frag");

    glUseProgram(shader->id());

    std::cout << modelMat;

    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));
    // glUniformMatrix4fv(glGetUniformLocation(shader->id(),"color"),1,GL_FALSE,&(projectionMat[0][0]));

    glUniform4fv(glGetUniformLocation(shader->id(),"color"), 1, &color[0]);

    mesh->drawVAO();

    glUseProgram(0);

    glLineWidth(2);

    glBegin(GL_LINES);


    glVertex3f(0.2,0.5,-1);
    glVertex3f(0.5,0.5,-1);

    glEnd();

    delete shader;
    delete mesh;

}

void CameraRenderer::createUI(){

    ImGui::Text("Line length : ");
    ImGui::DragFloat("##lineLength", &m_lineLength, 0.01f,0.01f, 1000.f); 

}