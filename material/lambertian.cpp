

#include "../imgui/imgui.h"
#include "../impl/imgui_impl_glfw.h"
#include "../impl/imgui_impl_opengl3.h"


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "lambertian.h"


Lambertian::Lambertian(glm::vec4 color){

    this->color = color;
    createShader();
    activeDebugNormal = false;

}
Lambertian::~Lambertian(){
    deleteShader();
}

void Lambertian::callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, glm::vec3 light){

    GLuint shaderID;
    if(activeDebugNormal){
        shaderID = debugNormalShader->id();
    } else {
        shaderID = shader->id();
    }

    glUniformMatrix4fv(glGetUniformLocation(shaderID,"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"projMat"),1,GL_FALSE,&(projMat[0][0]));

    // printf("y = %f\n", light[1]);

    if(!activeDebugNormal){

        glUniform3fv(glGetUniformLocation(shaderID,"light"), 1, &light[0]);

        glUniform4fv(glGetUniformLocation(shaderID,"color"),1,&(color[0]));
    }
}


void Lambertian::createUI(){
    // to hide label of the input
    ImGui::PushItemWidth(-1);

    ImGui::Text("Material");
    ImGui::Text("Color: "); ImGui::SameLine();
    ImGui::ColorEdit4("lambertian-color", (float *)&color);

    ImGui::Text("debug Normal "); ImGui::SameLine();
    ImGui::Checkbox("",&activeDebugNormal);

    // to hide label of the input
    ImGui::PopItemWidth();
}

GLuint Lambertian::shaderID(){
    GLuint shaderID;
    if(activeDebugNormal){
        shaderID = debugNormalShader->id();
    } else {
        shaderID = shader->id();
    }
    return shaderID;
}


void Lambertian::createShader(){
    shader = new Shader();
    shader->load("material/shaders/lambertian.vert","material/shaders/lambertian.frag");
    debugNormalShader = new Shader();
    debugNormalShader->load("material/shaders/debugNormal.vert","material/shaders/debugNormal.frag");
}

void Lambertian::deleteShader(){
    delete shader; shader = NULL;
    delete debugNormalShader; debugNormalShader = NULL;
}
