#include "rigidbody.h"
#include "../engineClass/mainRenderer.h"

#include <iostream>

#include "colliders/collider.h"

#ifndef M_PI
#define M_PI 3.1415926
#endif


Rigidbody::Rigidbody(float speed) : m_speed(speed), m_velocity(glm::vec3(0)), m_vectorMove(glm::vec3(0)), m_jumpForce(1.3f), m_useGravity(true), m_mass(0.15f) {
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
        Collider* collider = m_gameobject->getComponent<Collider*>();
        if(collider != nullptr && collider->getActive()){
            if(collider->isGrounded()){
                input.y = 1.0f;
            }
        }
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
    

    float yMove = m_vectorMove.y + input.y*m_jumpForce;
    

    m_vectorMove = pos - m_gameobject->getTransform()->getPosition(); 
    m_vectorMove.y = yMove;
}

void Rigidbody::update() {
    extern float global_limitFramerate;


    glm::vec3 pos = m_gameobject->getTransform()->getPosition();


    computeGravity();

    m_vectorMove.x *= m_speed;
    m_vectorMove.z *= m_speed;


    assert(global_limitFramerate != 0.0f);
    float deltaTime = ImGui::GetIO().Framerate / global_limitFramerate;
    m_vectorMove *= deltaTime;
    // printf("Delta Y: %f\n", deltaTime);

    

    m_gameobject->m_transform->setPosition(pos+m_vectorMove); 

}

void Rigidbody::createUI() {
    ImGui::Text("Speed : ");
    ImGui::DragFloat("##speed", &m_speed, 0.01f,0.01f, 1000.f);
    ImGui::Text("Mass : ");
    ImGui::DragFloat("##mass", &m_mass, 0.01f,0.01f, 1000.f);
    ImGui::Text("Jump Force : ");
    ImGui::DragFloat("##jump", &m_jumpForce, 0.01f,0.01f, 1000.f);
    ImGui::Text("Use gravity: "); ImGui::SameLine();
    ImGui::Checkbox("##useGravity", &m_useGravity);
    ImGui::Text("Vector move : (%4f, %4f, %4f)", m_vectorMove.x, m_vectorMove.y, m_vectorMove.z);
}


void Rigidbody::computeGravity() {
    if(m_useGravity){

        m_vectorMove.y -= m_mass*m_gameobject->getTransform()->getScale().y;

        Collider* collider = m_gameobject->getComponent<Collider*>();
        if(collider != nullptr && collider->getActive()){
            if(collider->isGrounded() && m_vectorMove.y < 0){
                m_vectorMove.y = 0.0f;
            }
        }
    }
}
