#ifndef CAMERA_H
#define CAMERA_H


#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif


#include "../engineClass/gameObject.h"

class Camera : public GameObject {


public:
    virtual glm::mat4 getProj(float aspect = 16./9.) = 0;
    glm::mat4 getView(){return m_transform->getModelMat();}


protected:

};

#endif
