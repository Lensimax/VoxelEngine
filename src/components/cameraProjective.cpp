#include "cameraProjective.h"
#include <imgui.h>

CameraProjective::CameraProjective(float fov, float near, float far) : m_fov(fov), m_near(near), m_far(far){
    setName("Camera");
}

glm::mat4 CameraProjective::getProj(float aspect){
    return glm::perspective(m_fov, aspect, m_near, m_far);
}

void CameraProjective::createUI(){
    ImGui::Text("Fov: "); ImGui::SameLine();
    ImGui::DragFloat("##fov", &m_fov, 0.01f);
    ImGui::Text("Near: "); ImGui::SameLine();
    ImGui::DragFloat("##near", &m_near, 0.01f); //ImGui::SameLine();
    ImGui::Text("Far: "); ImGui::SameLine();
    ImGui::DragFloat("##far", &m_far, 0.01f);
}