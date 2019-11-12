#include "textureMaterial.h"

#include <imgui.h>

#include "../images_loader/stb_image.h"


TextureMaterial::TextureMaterial(char file[2048]){

    createShader();

    sprintf(filename, "%s", file);

}


TextureMaterial::~TextureMaterial(){
    deleteShader();
}

void TextureMaterial::deleteShader(){
    delete shader;
}

void TextureMaterial::createUI(){
    // to hide label of the input

    if (ImGui::Button("Refresh")){
        reloadShaders();
    }

    ImGui::Text("Texture: "); ImGui::SameLine();
    ImGui::InputText("fileMeshLoader", filename, IM_ARRAYSIZE(filename));
}

void TextureMaterial::callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light){

    GLuint shaderID = shader->id();

    sendUniformMatrices(shaderID, modelMat, viewMat, projMat);

    glUniform1i(glGetUniformLocation(shaderID,"tex"),1);


}

GLuint TextureMaterial::getShaderID(){
    return shader->id();
}

void TextureMaterial::createShader(){
    shader = new Shader();
    shader->load(textureShaderVert,textureShaderFrag);
}
void TextureMaterial::reloadShaders(){
    shader->reload(textureShaderVert,textureShaderFrag);
}
