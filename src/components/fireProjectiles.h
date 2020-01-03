#ifndef FIREPROJECTILES_H
#define FIREPROJECTILES_H

#include "component.h"
#include "../engineClass/scene.h"

class FireProjectiles : public Component {

public:
    FireProjectiles();
    ~FireProjectiles();

    void update() override;

    void setScene(Scene *scene){m_scene = scene;}
private:

    void createProjectile();

    Scene *m_scene;

};


#endif