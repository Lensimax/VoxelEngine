#include "thirdPersonController.h"
#include <imgui.h>

#include <iostream>

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

ThirdPersonController::ThirdPersonController() : m_sensitivity(glm::vec2(0.5f)){
    setName("Third Person Controller");
}



ThirdPersonController::~ThirdPersonController(){

}



void ThirdPersonController::update(){
    ImGuiIO& io = ImGui::GetIO();
    if(io.KeyCtrl && ImGui::IsKeyPressed('G')){
        m_active = !m_active;
    }
    if(!m_active){
        return;
    }

    if(m_camera == NULL){
        return;
    }


    // CAMERA EDITOR CONTROL
    if(!io.WantCaptureMouse){
        
        glm::vec3 rotation = m_gameobject->getTransform()->getRotation();
        glm::vec3 camrotation = m_camera->getTransform()->getRotation();

        glm::vec2 vectorMouse = glm::vec2(io.MouseDelta.x, io.MouseDelta.y);
        vectorMouse *= -1.0f;
        vectorMouse *= m_sensitivity*0.01f;

        rotation.y += vectorMouse.x;
        camrotation.x -= vectorMouse.y;
        camrotation.x = glm::clamp(camrotation.x, 0.0f, 1.5f);

        m_gameobject->getTransform()->setRotation(rotation);
        m_camera->getTransform()->setRotation(camrotation);
    }

}


void ThirdPersonController::createUI(){
    ImGui::Text("Sensitivity : (x0.01)");
    ImGui::DragFloat2("##rotationsensitivity", &m_sensitivity[0], 0.01, 0.0, 100.);
}