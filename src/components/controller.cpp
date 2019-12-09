#include "controller.h"


void Controller::update(){

    glm::vec3 pos = m_gameobject->m_transform->getPosition();
    if(ImGui::IsKeyPressed('W')){
        pos.z -= m_speed;
    }
    if(ImGui::IsKeyPressed('S')){
        pos.z += m_speed;
    }
    if(ImGui::IsKeyPressed('A')){
        pos.x -= m_speed;
    }
    if(ImGui::IsKeyPressed('D')){
        pos.x += m_speed;
    }

    m_gameobject->m_transform->setPosition(pos); 

}