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

#include "colliders/collider.h"


Projectile::Projectile(float speed) : m_speed(speed){
    setName("Projectile");
}


Projectile::~Projectile(){

}

void Projectile::update(){

}

void Projectile::createUI(){
    Collider* collider = m_gameobject->getComponent<Collider*>();
    if(collider != nullptr){
        ImGui::Text("Is in collision : %s", collider->isInCollision() ? "true" : "false");
    }
}