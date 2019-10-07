

#include "camera.h"


void Camera::setAxis(glm::vec3 pos, glm::vec3 u, glm::vec3 dir){
    position = pos;
    up = u;
    directionOfView = dir;
}

glm::mat4 Camera::getView(){
    return glm::lookAt(position, directionOfView, up);
}
