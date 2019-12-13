#include "cameraProj.h"

#include <imgui.h>


CameraProj::CameraProj(int id, std::string name, glm::vec3 pos, glm::vec3 u, glm::vec3 direction, float fov, float n, float f) : m_fovy(fov), m_near(n), m_far(f){
    setName(name);
    setID(id);

    setAxis(pos, u, direction);

    m_pitch = 0;
    m_yaw = 0;
    m_roll = 0;

    /*glm::mat4 view = glm::mat4(1);
    view[0][0] = -1;
    view[2][2] = 0;
    view[1][3] = 1;
    view[2][3] = 3;


    m_transform->decompose(view);*/
}




void CameraProj::createUI(char *ID){
    const float lowestValue = -1000.0f;
    const float highestValue = 1000.0f;
    const char *format = "%.3f";

    ImGui::BeginChild(ID);
    ImGui::Text(m_name.c_str());
    ImGui::Separator();


    ImGui::PushItemWidth(-1);

    m_transform->createUI();

    /*ImGui::Text("Position: "); ImGui::SameLine();
    ImGui::DragFloat3("position", &m_position[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Up: "); ImGui::SameLine();
    ImGui::DragFloat3("Up", &m_up[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Direction: "); ImGui::SameLine();
    ImGui::DragFloat3("direction", &m_directionOfView[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Pitch: ");
    ImGui::DragFloat("##pitch", &m_pitch, 0.01f);
    ImGui::Text("Yaw: ");
    ImGui::DragFloat("##yaw", &m_yaw, 0.01f);*/
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
