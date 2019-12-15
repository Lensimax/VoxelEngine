#include "cameraFollow.h"

#include <imgui.h>

#include "cameraProjective.h"


CameraFollow::CameraFollow(float distance, float offsetAngle) : m_distanceFromPlayer(distance), m_angleOffset(offsetAngle){
    setName("Camera Follow");
    m_player = NULL;
}


CameraFollow::~CameraFollow(){

}

void CameraFollow::update(){
    if(m_player == NULL){
        return;
    }

    updateCameraPositionFromPlayer();
    

}

void CameraFollow::createUI(){
    ImGui::Text("Distance from the player : ");
    ImGui::DragFloat("##distance", &m_distanceFromPlayer, 0.01f,0.01f, 1000.f); 
    ImGui::Text("Offset angle : ");
    ImGui::DragFloat("##offsetangle", &m_angleOffset, 0.01f,-50.f, 50.f); 
}


float CameraFollow::getHorizontalDistance(){
    return m_distanceFromPlayer * cos(m_gameobject->getTransform()->getRotation().x);
}

float CameraFollow::getVerticalDistance(){
    return m_distanceFromPlayer * sin(m_gameobject->getTransform()->getRotation().x);
}

void CameraFollow::updateCameraPositionFromPlayer(){
    if(m_player == NULL){
        return;
    }

    float vertical = getVerticalDistance();
    float horizontal = getHorizontalDistance();
    float theta = m_player->getTransform()->getRotation().y + m_angleOffset;

    float offsetX = horizontal * sin(theta);
    float offsetZ = horizontal * cos(theta);

    glm::vec3 position = m_player->getTransform()->getPosition();
    position.x -= offsetX;
    position.y += vertical;
    position.z -= offsetZ;

    m_gameobject->getTransform()->setPosition(position);
    glm::vec3 rotation = m_gameobject->getTransform()->getRotation();
    rotation.y = 3.14159f - theta;
    m_gameobject->getTransform()->setRotation(rotation);
}