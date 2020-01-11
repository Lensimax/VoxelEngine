#include "rigidbody.h"
#include "../engineClass/mainRenderer.h"

#include <iostream>

#include "colliders/collider.h"

#define M_PI 3.14159265359


Rigidbody::Rigidbody() : m_speed(0.5f), m_vectorMove(glm::vec3(0)), m_useGravity(true), m_mass(0.15f) {
    setName("Rigidbody");
}

void Rigidbody::inputUpdate() {


    glm::vec3 input = glm::vec3(0.0f);

    if(ImGui::IsKeyPressed('W')){
        input.z = 1.0f;
    }
    if(ImGui::IsKeyPressed('S')){
        input.z = -1.0f;
    }
    if(ImGui::IsKeyPressed('A')){
        input.x = -1.0f;
    }
    if(ImGui::IsKeyPressed('D')){
        input.x = 1.0f;
    }
    if(ImGui::IsKeyPressed(' ')) { // barre espace
        input.y = 1.0f;
    }

    glm::vec3 pos = m_gameobject->getTransform()->getPosition();
    glm::vec3 rotation = m_gameobject->getTransform()->getRotation();
    float dx = glm::cos(rotation.y);
    float dz = glm::sin(rotation.y);

    float dxx = glm::cos(M_PI - rotation.y);
    float dzx = glm::sin(M_PI - rotation.y);

    pos.z += input.z * dx;
    pos.x += input.z * dz;
    pos.z += input.x * dzx;
    pos.x += input.x * dxx;
    pos.y += input.y;

    m_vectorMove = pos - m_gameobject->getTransform()->getPosition(); 
}

void Rigidbody::update() {
    extern float global_limitFramerate;


    glm::vec3 pos = m_gameobject->getTransform()->getPosition();


    // printf("Avant Player Y: %f\n", m_gameobject->getTransform()->getPosition().y);
    computeGravity();

    m_vectorMove.x *= m_speed;
    m_vectorMove.z *= m_speed;


    assert(global_limitFramerate != 0.0f);
    float deltaTime = ImGui::GetIO().Framerate / global_limitFramerate;
    m_vectorMove *= deltaTime;
    printf("Delta Y: %f\n", deltaTime);

    

    m_gameobject->m_transform->setPosition(pos+m_vectorMove); 

    // printf("Après Player Y: %f\n", m_gameobject->getTransform()->getPosition().y);
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

        m_vectorMove.y = -m_mass*m_gameobject->getTransform()->getScale().y;

        Collider* collider = m_gameobject->getComponent<Collider*>();
        if(collider != nullptr && collider->getActive()){
            if(collider->isGrounded()){
                m_vectorMove.y = 0.0f;
            }
        }
    }
}
