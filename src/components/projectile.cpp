#include "projectile.h"

#ifndef M_PI
#define M_PI 3.1415926
#endif

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "../engineClass/gameObject.h"

#include <imgui.h>


Projectile::Projectile(float speed) : m_speed(speed){
    setName("Projectile");
}


Projectile::~Projectile(){

}

void Projectile::update(){
    if(m_active){
        float deltaTime = ImGui::GetIO().Framerate/1000.f;

        glm::vec3 pos = m_gameobject->getTransform()->getPosition();
        glm::vec3 rotation = m_gameobject->getTransform()->getRotation();

        float dx = glm::cos(rotation.y);
        float dz = glm::sin(rotation.y);

        float dxx = glm::cos(M_PI - rotation.y);
        float dzx = glm::sin(M_PI - rotation.y);

        glm::vec3 move = glm::vec3(0, 0, 0);
        move.z = 1.0f;
        move *= deltaTime*m_speed;
        pos.z += move.z * dx;
        pos.x += move.z * dz;

        m_gameobject->m_transform->setPosition(pos); 
    }
}

void Projectile::createUI(){
    ImGui::Text("Speed : ");
    ImGui::DragFloat("##speed", &m_speed, 0.01f,0.01f, 1000.f);
}