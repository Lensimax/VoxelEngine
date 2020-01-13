#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "component.h"
#include "../engineClass/gameObject.h"

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


class Rigidbody : public Component {

public:
    Rigidbody(float speed = 0.5f);

    void update() override;

    void createUI() override;

    float getSpeed(){return m_speed;}
    void setSpeed(float speed){m_speed = speed;}
    float getMass(){return m_mass;}
    glm::vec3 getMove(){return m_vectorMove;}
    void setMove(glm::vec3 move){m_vectorMove = move;}
    bool useGravity(){return m_useGravity;}
    void setUseGravity(bool use){m_useGravity = use;}

private:
    void computeGravity();

    float m_speed, m_mass;
    bool m_useGravity;

    glm::vec3 m_vectorMove;
    glm::vec3 m_velocity;

};

#endif