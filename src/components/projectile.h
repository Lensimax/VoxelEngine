#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "component.h"

class Projectile : public Component {
public:
    Projectile(int radius = 5);
    ~Projectile();

    void update() override;
    void createUI() override;
    
private:
    float m_speed;
    int m_radiusOfExplosion;
};


#endif