#include "collider.h"


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


Collider::Collider(glm::vec3 box) : m_collidingBox(box), m_showCollidingBox(true) {
    setName("Collider");
}

Collider::~Collider() {
    
}

void Collider::update() {
    glm::vec3 position = m_gameobject->getTransform()->getPosition();
    m_top = m_terrain->getVoxelAt(glm::vec3(position.x, position.y+m_collidingBox.y, position.z));
    m_bottom = m_terrain->getVoxelAt(glm::vec3(position.x, position.y-m_collidingBox.y, position.z));
}

void Collider::createUI() {
    ImGui::Text("Box Collider: ");
    ImGui::DragFloat3("##boxCollider", &m_collidingBox[0], 0.01f, 0.01f, 10.f, "%.3f");

    if(m_terrain != nullptr){
        glm::vec3 position = m_gameobject->getTransform()->getPosition();
        ImGui::Text("Position: (%f, %f, %f)", position.x, position.y, position.z);

        Voxel voxel = m_terrain->getVoxelAt(position);
        displayImGuiVoxel(voxel, "test");

        displayImGuiVoxel(m_top, "Top");
        displayImGuiVoxel(m_bottom, "Bottom");

    }
}




void Collider::displayImGuiVoxel(Voxel voxel, const char message[]) {
    if(voxel == Voxel::Empty){
        ImGui::Text("%s : Empty", message);
    } else {
        ImGui::Text("%s : Full", message);
    }    
}
