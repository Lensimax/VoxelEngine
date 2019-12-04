#include "cameraProj.h"

#include <imgui.h>


CameraProj::CameraProj(int id, std::string name, glm::vec3 pos, glm::vec3 u, glm::vec3 direction, float fov, float n, float f) : m_fovy(fov), m_near(n), m_far(f){
    setName(name);
    setID(id);

    setAxis(pos, u, direction);
}




void CameraProj::createUI(char *ID){
    const float lowestValue = -1000.0f;
    const float highestValue = 1000.0f;
    const char *format = "%.3f";

    ImGui::BeginChild(ID);
    ImGui::Text(m_name.c_str());
    ImGui::Separator();


    ImGui::PushItemWidth(-1);

    ImGui::Text("Position: "); ImGui::SameLine();
    ImGui::DragFloat3("position", &m_position[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Up: "); ImGui::SameLine();
    ImGui::DragFloat3("Up", &m_up[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Direction: "); ImGui::SameLine();
    ImGui::DragFloat3("direction", &m_directionOfView[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Separator();
    ImGui::Text("Fov: "); ImGui::SameLine();
    ImGui::DragFloat("fov", &m_fovy, 0.01f);
    ImGui::Text("Near: "); ImGui::SameLine();
    ImGui::DragFloat("near", &m_near, 0.01f); //ImGui::SameLine();
    ImGui::Text("Far: "); ImGui::SameLine();
    ImGui::DragFloat("far", &m_far, 0.01f);


    ImGui::PopItemWidth();

    ImGui::EndChild();
}



glm::mat4 CameraProj::getProj(float aspect){
    return glm::perspective(m_fovy, aspect, m_near, m_far);
}
