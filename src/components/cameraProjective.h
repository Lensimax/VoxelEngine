#ifndef CAMERAPROJECTIVE_H
#define CAMERAPROJECTIVE_H

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "component.h"


class CameraProjective : public Component {

public:
    CameraProjective(float fov = 45.f, float near = 0.1f, float far = 1000.f);


    virtual glm::mat4 getProj(float aspect = 16./9.);

    void createUI() override final;

protected:

    float m_fov;
    float m_near;
    float m_far;


};

#endif