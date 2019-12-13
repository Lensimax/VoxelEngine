#include "cameraProj.h"

#include <imgui.h>


CameraProj::CameraProj(int id, std::string name, Transform *transform, float fov, float n, float f) : m_fovy(fov), m_near(n), m_far(f){
    setName(name);
    setID(id);
    m_transform = transform;

 
}




void CameraProj::createUI(char *ID){
    const float lowestValue = -1000.0f;
    const float highestValue = 1000.0f;
    const char *format = "%.3f";

    ImGui::BeginChild(ID);
    ImGui::Text(m_name.c_str());
    ImGui::Separator();

    glm::vec3 position = m_transform->getPosition();
    glm::vec3 rotation = m_transform->getRotation();

    ImGui::Text("Transform");
    ImGui::Text("Position: "); ImGui::SameLine();
    ImGui::DragFloat3("##position", &position[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Rotation: "); ImGui::SameLine();
    ImGui::DragFloat3("##rotation", &rotation[0], 0.01f, lowestValue, highestValue, format);

    m_transform->setPosition(position);
    m_transform->setRotation(rotation);

    ImGui::Separator();

    ImGui::Text("Fov: "); ImGui::SameLine();
    ImGui::DragFloat("##fov", &m_fovy, 0.01f);
    ImGui::Text("Near: "); ImGui::SameLine();
    ImGui::DragFloat("##near", &m_near, 0.01f); //ImGui::SameLine();
    ImGui::Text("Far: "); ImGui::SameLine();
    ImGui::DragFloat("##far", &m_far, 0.01f);


    ImGui::EndChild();
}



glm::mat4 CameraProj::getProj(float aspect){
    return glm::perspective(m_fovy, aspect, m_near, m_far);
}
