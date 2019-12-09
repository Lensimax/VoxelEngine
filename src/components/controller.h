#ifndef CONTROLLER_H
#define CONTROLLER_H

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


class Controller : public Component {

public:

    void update() override;

    float m_speed = 0.2f;

private:


};

#endif