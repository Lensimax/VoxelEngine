

#include <imgui.h>

#include "camera.h"

#include <iostream>
// #include <glm_display.h>


void Camera::setAxis(glm::vec3 pos, glm::vec3 u, glm::vec3 dir){
    m_position = pos;
    /*m_up = u;
    m_directionOfView = dir;*/
}

glm::mat4 Camera::getView(){
    // return glm::lookAt(m_position, m_directionOfView, m_up);
    glm::mat4 viewMat = m_model;
    viewMat = glm::rotate(viewMat, m_pitch, vec3(1.0,0.0,0.0));
    viewMat = glm::rotate(viewMat, m_yaw, vec3(0.0,1.0,0.0));

    viewMat = glm::translate(viewMat, glm::vec3(-m_position.x, -m_position.y, -m_position.z));
    //return viewMat;
    return m_transform->getModelMat();
}


/*glm::vec3 Camera::getLeftDir(){
    glm::vec3 v = m_directionOfView - m_position;
    return glm::normalize(-glm::cross(v, m_up));
}

glm::vec3 Camera::getRightDir(){
    glm::vec3 v = m_directionOfView - m_position;
    return glm::normalize(glm::cross(v, m_up));
}

*/



void Camera::update(){

}


void Camera::rotateAroundPoint(glm::vec2 v){


}
