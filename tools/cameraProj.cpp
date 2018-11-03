#include "cameraProj.h"


CameraProj::CameraProj(std::string name, glm::vec3 pos, glm::vec3 u, glm::vec3 direction, float fov, float aspectP, float n, float f){
    setName(name);

    setAxis(pos, u, direction);

    fovy = fov;
    aspect = aspectP;
    near = n;
    far = f;
}




glm::mat4 CameraProj::getMat4(){
    return glm::perspective(fovy, aspect, near, far);
}
