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

    const mat4 inverted = glm::inverse(m_gameobject->getTransform()->getModelMat());
    const vec3 forward = -1.0f*normalize(glm::vec3(inverted[2]));

    glm::vec3 pos = m_gameobject->getTransform()->getPosition();
    pos += forward*0.1f;
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