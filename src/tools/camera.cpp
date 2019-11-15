

#include <imgui.h>

#include "camera.h"


void Camera::setAxis(glm::vec3 pos, glm::vec3 u, glm::vec3 dir){
    position = pos;
    up = u;
    directionOfView = dir;
}

glm::mat4 Camera::getView(){
    return glm::lookAt(position, directionOfView, up);
}


glm::vec3 Camera::getLeftDir(){
    glm::vec3 v = directionOfView - position;
    return glm::normalize(-glm::cross(v, up));
}

glm::vec3 Camera::getRightDir(){
    glm::vec3 v = directionOfView - position;
    return glm::normalize(glm::cross(v, up));
}


void Camera::update(){
    if(ImGui::IsKeyPressed('J')){
        glm::vec3 left = getLeftDir();
        position = position + left*0.2f;
    }

    if(ImGui::IsKeyPressed('L')){
        glm::vec3 right = getRightDir();
        position = position + right*0.2f;
    }
}
