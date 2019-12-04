#include <imgui.h>

#include "directionnalLight.h"

DirectionnalLight::DirectionnalLight(int id, std::string name, glm::vec3 l){
    setID(id);
    setName(name);
    light = l;
    intensity = 1.0;
}



glm::vec3 DirectionnalLight::getLight(){
    return light;
}

void DirectionnalLight::createUI(char *ID){
    const float lowestValue = -1000.0f;
    const float highestValue = 1000.0f;
    const char *format = "%.3f";

    ImGui::BeginChild(ID);
    ImGui::Text(m_name.c_str());
    ImGui::Separator();


    ImGui::PushItemWidth(-1);

    ImGui::Text("Direction: "); ImGui::SameLine();
    ImGui::DragFloat3("directionLight", &light[0], 0.01f, lowestValue, highestValue, format);

    ImGui::Text("Intensity: "); ImGui::SameLine();
    ImGui::DragFloat("intensity", &intensity, 0.01f, 0.0, 2.0, "%.3f");


    ImGui::PopItemWidth();

    ImGui::EndChild();
}
