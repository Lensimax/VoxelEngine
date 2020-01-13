#include "playerController.h"

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <imgui.h>
#include "colliders/collider.h"
#include "rigidbody.h"

#ifndef M_PI
#define M_PI 3.1415926
#endif



PlayerController::PlayerController() : m_jumpForce(1.3f) {
    setName("Player Controller");
}

void PlayerController::inputUpdate() {
    Rigidbody *rb = m_gameobject->getComponent<Rigidbody*>();
    if(rb == nullptr){
        return;
    }

    
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

    glm::vec3 vectorMove = rb->getMove();
    

    float yMove = vectorMove.y + input.y*m_jumpForce;
    

    vectorMove = pos - m_gameobject->getTransform()->getPosition(); 
    vectorMove.y = yMove;
    
    rb->setMove(vectorMove);
}


void PlayerController::createUI(){
    ImGui::Text("Jump Force : ");
    ImGui::DragFloat("##jump", &m_jumpForce, 0.01f,0.01f, 1000.f);
}
