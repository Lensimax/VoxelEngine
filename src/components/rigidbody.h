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
    Rigidbody();

    void inputUpdate() override;
    void update() override;

    void createUI() override;

    float m_speed;
    glm::vec3 m_move;

private:


};

#endif