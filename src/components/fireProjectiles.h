#ifndef FIREPROJECTILES_H
#define FIREPROJECTILES_H

#include "component.h"
#include "../engineClass/scene.h"

class FireProjectiles : public Component {

public:
    FireProjectiles();
    ~FireProjectiles();

    void inputUpdate() override;
    void createUI() override;

    void setScene(Scene *scene){m_scene = scene;}
private:
    glm::vec3 computeForward();
    void createProjectile();

    Scene *m_scene;
    float m_projectileSpeed;

};


#endif