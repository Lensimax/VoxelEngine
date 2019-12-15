#include "cameraProjective.h"
#include <imgui.h>

#include "../engineClass/gameObject.h"

CameraProjective::CameraProjective(float fov, float near, float far) : m_fov(fov), m_near(near), m_far(far){
    setName("Camera");
}


glm::mat4 CameraProjective::getView(){
    glm::mat4 viewMat = glm::mat4(1);

    glm::vec3 rotation = m_gameobject->getTransform()->getRotation();

    viewMat = glm::rotate(viewMat, rotation.x, glm::vec3(1.0,0.0,0.0));
    viewMat = glm::rotate(viewMat, rotation.y, glm::vec3(0.0,1.0,0.0));
    viewMat = glm::translate(viewMat, m_gameobject->getTransform()->getPosition()*(-1.0f));
    // on applique pas de roll
    //viewMat = glm::rotate(viewMat, rotation.z, glm::vec3(0.0,0.0,1.0));

    return viewMat;
}

glm::mat4 CameraProjective::getProjection(float aspect){
    return glm::perspective(m_fov, aspect, m_near, m_far);
}

void CameraProjective::createUI(){
    const float min = 0.001f;
    const float max = 1000000.0f;

    ImGui::Text("Fov: "); ImGui::SameLine();
    ImGui::DragFloat("##fov", &m_fov, 0.01f, min, max);
    ImGui::Text("Near: "); ImGui::SameLine();
    ImGui::DragFloat("##near", &m_near, 0.01f, min, max); //ImGui::SameLine();
    ImGui::Text("Far: "); ImGui::SameLine();
    ImGui::DragFloat("##far", &m_far, 0.01f, min, max);
}