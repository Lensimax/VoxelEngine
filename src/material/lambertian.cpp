

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

using namespace glm;

Lambertian::Lambertian(glm::vec4 color){


    createShader();
    activeDebugNormal = false;

    specularDeg = 2;
    ambientColor = vec4(0.0,0.0,0.0,0.0);
    diffuseColor = color;
    specularColor = vec4(255./255.,255./255.,255./255.,1.0);

}
Lambertian::~Lambertian(){
    deleteShader();
}


void Lambertian::callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light){

    GLuint shaderID = getShaderID();

    sendUniformMatrices(shaderID, modelMat, viewMat, projMat);



    // printf("y = %f\n", light[1]);

    if(!activeDebugNormal){

        glm::vec4 lightVec;
        glm::vec3 vec = light->getLight();
        lightVec.x = vec.x;
        lightVec.y = vec.y;
        lightVec.z = vec.z;
        lightVec.w = 1;

        glm::mat4 normalMatrix = viewMat * modelMat;
        normalMatrix = inverseTranspose(normalMatrix);

        glUniformMatrix4fv(glGetUniformLocation(shaderID,"normalMatrix"),1,GL_FALSE,&(normalMatrix[0][0]));

        glUniformMatrix4fv(glGetUniformLocation(shaderID,"lightMat4"),1,GL_FALSE,&(modelMat[0][0]));

        glUniform4fv(glGetUniformLocation(shaderID,"light"), 1, &(lightVec[0]));


        glUniform4fv(glGetUniformLocation(shaderID,"ambientColor"),1,&(ambientColor[0]));
        glUniform4fv(glGetUniformLocation(shaderID,"diffuseColor"),1,&(diffuseColor[0]));
        glUniform4fv(glGetUniformLocation(shaderID,"specularColor"),1,&(specularColor[0]));

        glUniform1f(glGetUniformLocation(shaderID,"specularDegree"), specularDeg);

    }
}


void Lambertian::createUI(){
    // to hide label of the input
    ImGui::PushItemWidth(-1);

    if (ImGui::Button("Refresh")){
        reloadShaders();
    }
    ImGui::Text("Diffuse Color: "); ImGui::SameLine();
    ImGui::ColorEdit4("diffuse-color", (float *)&diffuseColor);
    ImGui::Text("Ambient Color: "); ImGui::SameLine();
    ImGui::ColorEdit4("ambient-color", (float *)&ambientColor);
    ImGui::Text("Specular Color: "); ImGui::SameLine();
    ImGui::ColorEdit4("spec-color", (float *)&specularColor);

    ImGui::Text("Specular degree"); ImGui::SameLine();
    ImGui::DragFloat("specdeg", &specularDeg, 0.01f, 0.001f, 10000, "%.3f");

    ImGui::Text("debug Normal "); ImGui::SameLine();
    ImGui::Checkbox("debugNormal",&activeDebugNormal);

    // to hide label of the input
    ImGui::PopItemWidth();
}

GLuint Lambertian::getShaderID(){
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
    shader->load(lambertianShaderVert,lambertianShaderFrag);
    debugNormalShader = new Shader();
    debugNormalShader->load(debugShaderVert,debugShaderFrag);
}
void Lambertian::reloadShaders(){
    shader->reload(lambertianShaderVert,lambertianShaderFrag);
    debugNormalShader->reload(debugShaderVert, debugShaderFrag);
}

void Lambertian::deleteShader(){
    delete shader; shader = NULL;
    delete debugNormalShader; debugNormalShader = NULL;
}
