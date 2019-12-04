#include "simpleMat.h"



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

using namespace glm;

SimpleMat::SimpleMat(glm::vec4 color) : m_color(color){


    createShader();


}
SimpleMat::~SimpleMat(){
    deleteShader();
}


void SimpleMat::callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light){


    GLuint shaderID = m_shader->id();

    sendUniformMatrices(shaderID, modelMat, viewMat, projMat);

    glUniform4fv(glGetUniformLocation(shaderID,"color"),1,&(m_color[0]));

}


void SimpleMat::createUI(){
    // to hide label of the input

    if (ImGui::Button("Refresh")){
        reloadShaders();
    }
    ImGui::Text("Color: "); ImGui::SameLine();
    ImGui::ColorEdit4("##color", (float *)&m_color);
}


GLuint SimpleMat::getShaderID(){
    return m_shader->id();
}


void SimpleMat::createShader(){
    m_shader = new Shader();
    m_shader->load(m_simpleShaderVert,m_simpleShaderFrag);
}
void SimpleMat::reloadShaders(){
    m_shader->reload(m_simpleShaderVert,m_simpleShaderFrag);
}

void SimpleMat::deleteShader(){
    delete m_shader; m_shader = NULL;
}
