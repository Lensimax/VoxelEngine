#include <imgui.h>

#include "cameraTransform.h"

CameraTransform::CameraTransform(vec3 position, vec3 rotation){
    Transform();

    m_test = glm::mat4(1);

    m_position = position;
    m_rotation = rotation;
}


CameraTransform::~CameraTransform(){

}


mat4 CameraTransform::getModelMat(mat4 modelMat){
    // modelMat = translate(modelMat, center);
    modelMat = glm::rotate(modelMat, m_rotation[0]+m_animRotX, vec3(1.0,0.0,0.0));
    modelMat = glm::rotate(modelMat, m_rotation[1]+m_animRotY, vec3(0.0,1.0,0.0));
    modelMat = glm::rotate(modelMat, m_rotation[2]+m_animRotZ, vec3(0.0,0.0,1.0));
    //modelMat = translate(modelMat, m_translateAfter);
    modelMat = translate(modelMat, -m_position);
    m_test = modelMat;
    return modelMat;
}

void CameraTransform::createUI(){
    const float lowestValue = -1000.0f;
    const float highestValue = 1000.0f;


    // format d'affichage
    const char *format = "%.3f";

    
    ImGui::Text("Transform");
    ImGui::Text("Position: "); ImGui::SameLine();
    ImGui::DragFloat3("##position", &m_position[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Rotation: "); ImGui::SameLine();
    ImGui::DragFloat3("##rotation", &m_rotation[0], 0.01f, lowestValue, highestValue, format);

    ImGui::Separator();
    ImGui::Text("[%4f, %4f, %4f, %4f\n%4f, %4f, %4f, %4f\n%4f, %4f, %4f, %4f\n%4f, %4f, %4f, %4f]\n", m_test[0][0], m_test[0][1], m_test[0][2], m_test[0][3], m_test[1][0],
    m_test[1][1], m_test[1][2], m_test[1][3], m_test[2][0], m_test[2][1], m_test[2][2], m_test[2][3], m_test[3][0], m_test[3][1], m_test[3][2], m_test[3][3]);

   


}