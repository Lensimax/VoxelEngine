

#include <imgui.h>

#include "camera.h"

#include <iostream>
#include <glm_display.h>


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

}


void Camera::rotateAroundPoint(glm::vec2 v){


}
