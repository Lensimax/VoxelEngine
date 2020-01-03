#include "fireProjectiles.h"

#include "meshRenderer.h"
#include "../models/mesh/meshCube.h"
#include "../material/lambertian.h"

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
    projectile->addComponent<MeshRenderer*>(new MeshRenderer());
    // projectile->addComponent<Mesh*>(new MeshCube(0.5f));
    // projectile->addComponent<Material*>(new Lambertian());

    // m_scene->addGameObject(projectile);
    m_scene->addCube();

}