#include "rigidbody.h"
#include "../engineClass/mainRenderer.h"

#include <iostream>

#include "colliders/collider.h"

#ifndef M_PI
#define M_PI 3.1415926
#endif


Rigidbody::Rigidbody(float speed) : m_speed(speed), m_velocity(glm::vec3(0)), m_vectorMove(glm::vec3(0)), m_useGravity(false), m_mass(0.15f) {
    setName("Rigidbody");
}


void Rigidbody::update() {
    extern float global_limitFramerate;


    glm::vec3 pos = m_gameobject->getTransform()->getPosition();


    computeGravity();

    glm::vec3 currentMove = m_vectorMove;

    currentMove.x *= m_speed;
    currentMove.z *= m_speed;

    


    assert(global_limitFramerate != 0.0f);
    float deltaTime = ImGui::GetIO().Framerate / global_limitFramerate;
    currentMove *= deltaTime;
    // printf("Delta Y: %f\n", deltaTime);

    

    m_gameobject->m_transform->setPosition(pos+currentMove); 

}

void Rigidbody::createUI() {
    ImGui::Text("Speed : ");
    ImGui::DragFloat("##speed", &m_speed, 0.01f,0.01f, 1000.f);
    ImGui::Text("Mass : ");
    ImGui::DragFloat("##mass", &m_mass, 0.01f,0.01f, 1000.f);
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
