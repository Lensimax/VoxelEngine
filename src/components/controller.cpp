#include "controller.h"


Controller::Controller(){
    setName("Player Controller");
    m_speed = 0.2f;
}


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

void Controller::createUI(){
    ImGui::Text("Speed : ");
    ImGui::DragFloat("##speed", &m_speed, 0.01f,0.01f, 1000.f); 
}