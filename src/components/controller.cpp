#include "controller.h"


Controller::Controller(){
    setName("Player Controller");
    m_speed = 0.2f;
}


void Controller::update(){

    float deltaTime = ImGui::GetIO().Framerate/1000.f;

    glm::vec3 pos = m_gameobject->getTransform()->getPosition();
    glm::vec3 rotation = m_gameobject->getTransform()->getRotation();

    float dx = glm::cos(rotation.y);
    float dz = glm::sin(rotation.y);

    float dxx = glm::cos(M_PI - rotation.y);
    float dzx = glm::sin(M_PI - rotation.y);

    glm::vec3 move = glm::vec3(0, 0, 0);

    if(ImGui::IsKeyPressed('W')){
        move.z = 1.0f;
    }
    if(ImGui::IsKeyPressed('S')){
        move.z = -1.0f;
    }
    if(ImGui::IsKeyPressed('A')){
        move.x = -1.0f;
    }
    if(ImGui::IsKeyPressed('D')){
        move.x = 1.0f;
    }

    move *= deltaTime;

    pos.z += move.z * dx;
    pos.x += move.z * dz;
    pos.z += move.x * dzx;
    pos.x += move.x * dxx;

    m_gameobject->m_transform->setPosition(pos); 

}

void Controller::createUI(){
    ImGui::Text("Speed : ");
    ImGui::DragFloat("##speed", &m_speed, 0.01f,0.01f, 1000.f); 
}