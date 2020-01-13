#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "component.h"
#include "../engineClass/scene.h"

class Projectile : public Component {
public:
    Projectile(int radius = 5);
    ~Projectile();

    void update() override;
    void createUI() override;
    void setScene(Scene *scene){m_scene = scene;}
    void setPlayerTransform(Transform *transform){ m_playerTransform = transform;}
    
private:
    Transform *m_playerTransform;
    float m_speed;
    int m_radiusOfExplosion;
    Scene *m_scene;
};


#endif