

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

Lambertian::Lambertian(glm::vec4 color) : m_activeDebugNormal(false), m_specularDeg(2), m_ambientColor(vec4(0.0,0.0,0.0,0.0)), m_diffuseColor(color), m_specularColor(vec4(255./255.,255./255.,255./255.,1.0)){


    createShader();


}
Lambertian::~Lambertian(){
    deleteShader();
}


void Lambertian::callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light){

    GLuint shaderID = getShaderID();

    sendUniformMatrices(shaderID, modelMat, viewMat, projMat);



    // printf("y = %f\n", light[1]);

    if(!m_activeDebugNormal){

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

        int boolUseDiffuse = m_displayDiffuse ? 1 : 0;
        glUniform1i(glGetUniformLocation(shaderID,"boolUseDiffuse"), boolUseDiffuse);
        glUniform4fv(glGetUniformLocation(shaderID,"ambientColor"),1,&(m_ambientColor[0]));
        glUniform4fv(glGetUniformLocation(shaderID,"diffuseColor"),1,&(m_diffuseColor[0]));
        glUniform4fv(glGetUniformLocation(shaderID,"specularColor"),1,&(m_specularColor[0]));

        glUniform1f(glGetUniformLocation(shaderID,"m_specularDegree"), m_specularDeg);

    }
}


void Lambertian::createUI(){
    // to hide label of the input
    ImGui::PushItemWidth(-1);

    if (ImGui::Button("Refresh")){
        reloadShaders();
    }

    ImGui::Text("Display by diffuse color "); ImGui::SameLine();
    ImGui::Checkbox("##diffuseBool",&m_displayDiffuse); 
    if(m_displayDiffuse){
        ImGui::Text("Diffuse Color: "); ImGui::SameLine();
        ImGui::ColorEdit4("diffuse-color", (float *)&m_diffuseColor);
    }   
    ImGui::Text("Ambient Color: "); ImGui::SameLine();
    ImGui::ColorEdit4("##ambient-color", (float *)&m_ambientColor);
    ImGui::Text("Specular Color: "); ImGui::SameLine();
    ImGui::ColorEdit4("##spec-color", (float *)&m_specularColor);

    ImGui::Text("Specular degree"); ImGui::SameLine();
    ImGui::DragFloat("##specdeg", &m_specularDeg, 0.01f, 0.001f, 10000, "%.3f");

    ImGui::Text("debug Normal "); ImGui::SameLine();
    ImGui::Checkbox("##debugNormal",&m_activeDebugNormal);

    // to hide label of the input
    ImGui::PopItemWidth();
}

GLuint Lambertian::getShaderID(){
    GLuint shaderID;
    if(m_activeDebugNormal){
        shaderID = m_debugNormalShader->id();
    } else {
        shaderID = shader->id();
    }
    return shaderID;
}


void Lambertian::createShader(){
    shader = new Shader();
    shader->load(m_lambertianShaderVert,m_lambertianShaderFrag);
    m_debugNormalShader = new Shader();
    m_debugNormalShader->load(m_debugShaderVert,m_debugShaderFrag);
}
void Lambertian::reloadShaders(){
    shader->reload(m_lambertianShaderVert,m_lambertianShaderFrag);
    m_debugNormalShader->reload(m_debugShaderVert, m_debugShaderFrag);
}

void Lambertian::deleteShader(){
    delete shader; shader = NULL;
    delete m_debugNormalShader; m_debugNormalShader = NULL;
}
