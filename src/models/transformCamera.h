#ifndef TRANSFORMCAMERA_H
#define TRANSFORMCAMERA_H

#include "transform.h"

class TransformCamera : public Transform {

    mat4 getModelMat(mat4 modelMat = glm::mat4(1)){
        modelMat = glm::rotate(modelMat, m_rotation[0]+m_animRotX, vec3(1.0,0.0,0.0));
        modelMat = glm::rotate(modelMat, m_rotation[1]+m_animRotY, vec3(0.0,1.0,0.0));
        modelMat = glm::rotate(modelMat, m_rotation[2]+m_animRotZ, vec3(0.0,0.0,1.0));
        modelMat = translate(modelMat, m_position);
        return modelMat;
    }

};

#endif