#include "fireProjectiles.h"

#include "meshRenderer.h"
#include "../models/mesh/meshCube.h"
#include "../material/lambertian.h"
#include "projectile.h"
#include "axisRenderer.h"
#include "debug/debugTransform.h"
#include "colliders/collider.h"
#include "rigidbody.h"
#include "terrainModificator.h"

#include <imgui.h>
#include <iostream>

FireProjectiles::FireProjectiles() : m_projectileSpeed(0.2f), m_radiusExplosionProjectile(5){
    setName("Fire Projectiles");
}


FireProjectiles::~FireProjectiles(){
    
}

void FireProjectiles::inputUpdate(){
    if(!getActive()){
        return;
    }
    if(ImGui::IsKeyPressed('F')){
        createProjectile();
    }
}

glm::vec3 FireProjectiles::computeForward(){
    glm::vec3 input = glm::vec3(0,0,-1);
    glm::vec3 pos = m_gameobject->getTransform()->getPosition();
    glm::vec3 rotation = m_gameobject->getTransform()->getRotation();
    float dx = glm::cos(rotation.y);
    float dz = glm::sin(rotation.y);

    pos.z += input.z * dx;
    pos.x += input.z * dz;

    glm::vec3 vect = glm::normalize(m_gameobject->getTransform()->getPosition() - pos);

    return vect;
}

void FireProjectiles::createProjectile(){
    


    Transform *transf = new Transform();

    const vec3 forward = computeForward();

    glm::vec3 pos = m_gameobject->getTransform()->getPosition();
    pos += forward*0.5f;
    transf->setPosition(pos);
    transf->setRotation(m_gameobject->getTransform()->getRotation());

    // Creation Rigidbody
    Rigidbody *rb = new Rigidbody();
    rb->setUseGravity(false);
    rb->setMove(forward);
    rb->setSpeed(m_projectileSpeed);

    GameObject *projectile = new GameObject(m_scene->addNewId(), "Projectile", transf);
    projectile->addComponent<Mesh*>(new MeshCube(0.2f));
    projectile->addComponent<Material*>(new Lambertian()); 
    projectile->addComponent<Rigidbody*>(rb);
    projectile->addComponent<MeshRenderer*>(new MeshRenderer());
    projectile->getComponent<Lambertian*>()->toggleDisplayDiffuse();
    projectile->addComponent<Collider*>(new Collider(glm::vec3(0.25f)));
    projectile->getComponent<Collider*>()->setTerrain(m_terrain);
  
    projectile->addComponent<TerrainModificator*>(new TerrainModificator());
    projectile->getComponent<TerrainModificator*>()->setTerrain(m_terrain);
    projectile->addComponent<Projectile*>(new Projectile(m_radiusExplosionProjectile));

    // debug
    // projectile->addComponent<AxisRenderer*>(new AxisRenderer());
    // projectile->addComponent<DebugTransform*>(new DebugTransform());

    m_scene->addGameObject(projectile);

}



void FireProjectiles::createUI() {
    ImGui::Text("Projectile Speed : ");
    ImGui::DragFloat("##speed", &m_projectileSpeed, 0.01f,0.01f, 1000.f);
    ImGui::Text("Radius of explosion : ");
    ImGui::DragInt("##radius", &m_radiusExplosionProjectile, 1, 1, 100);
}