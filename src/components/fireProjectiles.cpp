#include "fireProjectiles.h"

#include <imgui.h>

FireProjectiles::FireProjectiles(){
    setName("Fire Projectiles");
}


FireProjectiles::~FireProjectiles(){
    
}

void FireProjectiles::update(){
    if(ImGui::IsKeyPressed('F')){
        createProjectile();
    }
}

void FireProjectiles::createProjectile(){
    Transform *transf = new Transform();

    glm::vec3 pos = m_gameobject->getTransform()->getPosition();
    pos.z = 0.5f;
    transf->setPosition(pos);
    transf->setRotation(m_gameobject->getTransform()->getRotation());

    GameObject *projectile = new GameObject(m_scene->addNewId(), "Projectile", transf);

    m_scene->addGameObject(projectile);

}