#include "rigidbody.h"
#include "../engineClass/mainRenderer.h"

#include <iostream>

#include "colliders/collider.h"

#define M_PI 3.14159265359


Rigidbody::Rigidbody() : m_speed(0.5f), m_move(glm::vec3(0)), m_useGravity(false), m_mass(0.15f) {
    setName("Rigidbody");
}

void Rigidbody::inputUpdate() {


    m_move.x = 0.0f; m_move.z = 0.0f;

    if(ImGui::IsKeyPressed('W')){
        m_move.z = 1.0f;
    }
    if(ImGui::IsKeyPressed('S')){
        m_move.z = -1.0f;
    }
    if(ImGui::IsKeyPressed('A')){
        m_move.x = -1.0f;
    }
    if(ImGui::IsKeyPressed('D')){
        m_move.x = 1.0f;
    }
    if(ImGui::IsKeyPressed(' ')) { // barre espace
        m_move.y = 1.0f;
    }
}

void Rigidbody::update() {
    extern float global_limitFramerate;


    glm::vec3 pos = m_gameobject->getTransform()->getPosition();
    glm::vec3 rotation = m_gameobject->getTransform()->getRotation();

    float dx = glm::cos(rotation.y);
    float dz = glm::sin(rotation.y);

    float dxx = glm::cos(M_PI - rotation.y);
    float dzx = glm::sin(M_PI - rotation.y);

    computeGravity();

    assert(global_limitFramerate != 0.0f);
    float deltaTime = ImGui::GetIO().Framerate / global_limitFramerate;
    m_move *= deltaTime*m_speed;

    pos.z += m_move.z * dx;
    pos.x += m_move.z * dz;
    pos.z += m_move.x * dzx;
    pos.x += m_move.x * dxx;
    pos.y += m_move.y;

    m_gameobject->m_transform->setPosition(pos); 

}

void Rigidbody::createUI() {
    ImGui::Text("Speed : ");
    ImGui::DragFloat("##speed", &m_speed, 0.01f,0.01f, 1000.f);
    ImGui::Text("Mass : ");
    ImGui::DragFloat("##mass", &m_mass, 0.01f,0.01f, 1000.f);
    ImGui::Text("Use gravity: "); ImGui::SameLine();
    ImGui::Checkbox("##useGravity", &m_useGravity);
}


void Rigidbody::computeGravity() {
    if(m_useGravity){

        m_move.y = -m_mass;

        Collider* collider = m_gameobject->getComponent<Collider*>();
        if(collider != nullptr){
            if(collider->isGrounded()){
                m_move.y = 0.0f;
            }
        }
    }
}
