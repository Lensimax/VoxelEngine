#include "cameraFollow.h"

#include <imgui.h>


CameraFollow::CameraFollow(float distance, float pitch) : m_distanceFromPlayer(distance), m_pitch(pitch){
    setName("Camera Follow");

}


CameraFollow::~CameraFollow(){

}

void CameraFollow::update(){

}

void CameraFollow::createUI(){
    ImGui::Text("Distance from the player : ");
    ImGui::DragFloat("##distance", &m_distanceFromPlayer, 0.01f,0.01f, 1000.f); 
    ImGui::Text("Line width : ");
    ImGui::DragFloat("##pitch", &m_pitch,0.2f, 1.0f, 1000.0f); 
}


float CameraFollow::getHorizontalDistance(){
    return m_distanceFromPlayer * cos(m_pitch);
}

float CameraFollow::getVerticalDistance(){
    return m_distanceFromPlayer * sin(m_pitch);
}