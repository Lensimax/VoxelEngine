#include "cameraProj.h"

#include <imgui.h>


CameraProj::CameraProj(int id, std::string name, glm::vec3 pos, glm::vec3 u, glm::vec3 direction, float fov, float n, float f){
    setName(name);
    setID(id);

    setAxis(pos, u, direction);

    fovy = fov;
    near = n;
    far = f;
}


void CameraProj::createUI(char *ID){
    const float lowestValue = -1000.0f;
    const float highestValue = 1000.0f;
    const char *format = "%.3f";

    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());
    ImGui::Separator();


    ImGui::PushItemWidth(-1);

    ImGui::Text("Position: "); ImGui::SameLine();
    ImGui::DragFloat3("position", &position[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Up: "); ImGui::SameLine();
    ImGui::DragFloat3("Up", &up[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Direction: "); ImGui::SameLine();
    ImGui::DragFloat3("direction", &directionOfView[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Separator();
    ImGui::Text("Fov: "); ImGui::SameLine();
    ImGui::DragFloat("fov", &fovy, 0.01f);
    ImGui::Text("Near: "); ImGui::SameLine();
    ImGui::DragFloat("near", &near, 0.01f); //ImGui::SameLine();
    ImGui::Text("Far: "); ImGui::SameLine();
    ImGui::DragFloat("far", &far, 0.01f);


    ImGui::PopItemWidth();

    ImGui::EndChild();
}



glm::mat4 CameraProj::getProj(float aspect){
    return glm::perspective(fovy, aspect, near, far);
}
