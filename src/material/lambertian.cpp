

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

#include "lambertian.h"

#include "../glm/gtc/matrix_inverse.hpp"


Lambertian::Lambertian(glm::vec4 color){

    this->color = color;
    createShader();
    activeDebugNormal = false;

    specularDeg = 2;
    ambientColor = vec3(0.1,0.1,0.1);
    specularColor = vec3(1.0,1.0,1.0);

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
        glm::mat4 normalMatrix = viewMat * modelMat;
        normalMatrix = glm::inverseTranspose(normalMatrix);

        glUniformMatrix4fv(glGetUniformLocation(shaderID,"normalMatrix"),1,GL_FALSE,&(normalMatrix[0][0]));

        glm::vec4 vecLight = glm::vec4(light, 1.0);

        glUniform4fv(glGetUniformLocation(shaderID,"light"), 1, &vecLight[0]);

        glUniform4fv(glGetUniformLocation(shaderID,"color"),1,&(color[0]));

        glUniform1f(glGetUniformLocation(shaderID,"specularDegree"), specularDeg);
    }
}


void Lambertian::createUI(){
    // to hide label of the input
    ImGui::PushItemWidth(-1);

    ImGui::Text("Material");
    ImGui::Text("Color: "); ImGui::SameLine();
    ImGui::ColorEdit4("lambertian-color", (float *)&color);

    ImGui::Text("Specular degree"); ImGui::SameLine();
    ImGui::DragFloat("specdeg", &specularDeg, 0.01f, 0.0, 100, "%.3f");

    ImGui::Text("Ambient color"); ImGui::SameLine();
    ImGui::ColorEdit4("ambient-color", (float *)&ambientColor);

    ImGui::Text("Specular color"); ImGui::SameLine();
    ImGui::ColorEdit4("specular-color", (float *)&specularColor);

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
