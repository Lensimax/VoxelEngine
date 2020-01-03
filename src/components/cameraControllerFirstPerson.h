#ifndef CAMERACONTROLLERFIRSTPERSON_H
#define CAMERACONTROLLERFIRSTPERSON_H

#include "component.h"

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif


class CameraControllerFirstPerson : public Component {
public:
    CameraControllerFirstPerson();
    ~CameraControllerFirstPerson();

    void update() override;

    void createUI() override;

private:


    glm::vec2 m_sensitivityRotateWorld;
    float m_scrollZoomSensitivity;

    

};


#endif