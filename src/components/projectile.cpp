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
#include "terrainModificator.h"


Projectile::Projectile(int radius) : m_radiusOfExplosion(radius){
    setName("Projectile");
}


Projectile::~Projectile(){

}

void Projectile::update(){
    Collider* collider = m_gameobject->getComponent<Collider*>();
    TerrainModificator* terainModif = m_gameobject->getComponent<TerrainModificator*>();
    if(collider == nullptr || terainModif == nullptr){
        return;
    }

    if(collider->isInCollision()){
        terainModif->destroy(m_radiusOfExplosion);
        assert(m_scene != nullptr);
        m_scene->addToDestroy(m_gameobject->getID());
    }
}

void Projectile::createUI(){
    Collider* collider = m_gameobject->getComponent<Collider*>();
    if(collider != nullptr){
        ImGui::Text("Is in collision : %s", collider->isInCollision() ? "true" : "false");
    }
    ImGui::Text("Radius of explosion : ");
    ImGui::DragInt("##radius", &m_radiusOfExplosion, 1, 1, 100);
}