#include "cameraFollow.h"

#include <imgui.h>


CameraFollow::CameraFollow(float distance, float pitch) : m_distanceFromPlayer(distance), m_pitch(pitch){
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
    ImGui::Text("Pitch : ");
    ImGui::DragFloat("##pitch", &m_pitch,0.2f, 1.0f, 1000.0f); 
}


float CameraFollow::getHorizontalDistance(){
    return m_distanceFromPlayer * cos(m_pitch);
}

float CameraFollow::getVerticalDistance(){
    return m_distanceFromPlayer * sin(m_pitch);
}

void CameraFollow::updateCameraPositionFromPlayer(){
    if(m_player == NULL){
        return;
    }

    const float angleOffset = 0.0f;
    float vertical = getVerticalDistance();
    float horizontal = getHorizontalDistance();
    float theta = m_player->getTransform()->getRotation().y + angleOffset;

    float offsetX = horizontal * sin(theta);
    float offsetZ = horizontal * cos(theta);

    glm::vec3 position = m_player->getTransform()->getPosition();
    position.x += offsetX;
    position.y += vertical;
    position.z += offsetZ;

    m_gameobject->getTransform()->setPosition(position);
    //m_gameobject->getTransform()->setRotation(glm::vec3(m_pitch, 0, 0));
}