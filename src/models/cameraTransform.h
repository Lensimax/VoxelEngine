#ifndef CAMERATRANSFORM_H
#define CAMERATRANSFORM_H

#include "transform.h"

class CameraTransform : public Transform {

public:
    CameraTransform(vec3 position = vec3(0.0,0.0,0.0), vec3 rotation = vec3(0.0,0.0,0.0));
    ~CameraTransform();

    mat4 getModelMat(mat4 modelMat) override;

    void createUI() override;

private:
    glm::mat4 m_test;

};

#endif