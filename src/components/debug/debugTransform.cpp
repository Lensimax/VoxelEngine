#include "debugTransform.h"

#include "../../engineClass/gameObject.h"

#include <imgui.h>

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif


void DebugTransform::createUI(){
    const glm::mat4 inverted = glm::inverse(m_gameobject->getTransform()->getModelMat());
    const glm::vec3 forward = normalize(glm::vec3(inverted[2]));
    const glm::vec3 left = normalize(glm::vec3(inverted[0]));
    const glm::vec3 top = normalize(glm::vec3(inverted[1]));

    ImGui::Separator();
    ImGui::Text("Forward (%f, %f, %f)", forward.x, forward.y, forward.z);
    ImGui::Text("Left (%f, %f, %f)", left.x, left.y, left.z);
    ImGui::Text("Top (%f, %f, %f)", top.x, top.y, top.z);
}