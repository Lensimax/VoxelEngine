#include "fireProjectiles.h"

#include "meshRenderer.h"
#include "../models/mesh/meshCube.h"
#include "../material/lambertian.h"
#include "projectile.h"

#include <imgui.h>
#include <iostream>

FireProjectiles::FireProjectiles(){
    setName("Fire Projectiles");
}


FireProjectiles::~FireProjectiles(){
    
}

void FireProjectiles::inputUpdate(){
    if(ImGui::IsKeyPressed('F')){
        createProjectile();
    }
}

void FireProjectiles::createProjectile(){
    Transform *transf = new Transform();

    glm::vec3 pos = m_gameobject->getTransform()->getPosition();
    pos.z += 0.5f;
    transf->setPosition(pos);
    transf->setRotation(m_gameobject->getTransform()->getRotation());

    GameObject *projectile = new GameObject(m_scene->addNewId(), "Projectile", transf);
    projectile->addComponent<Mesh*>(new MeshCube(0.2f));
    projectile->addComponent<Material*>(new Lambertian());
    projectile->addComponent<MeshRenderer*>(new MeshRenderer());
    projectile->getComponent<Lambertian*>()->toggleDisplayDiffuse();
    projectile->addComponent<Projectile*>(new Projectile());

    m_scene->addGameObject(projectile);

}