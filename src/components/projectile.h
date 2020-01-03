#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "component.h"

class Projectile : public Component {
public:
    Projectile(float speed = 0.5f);
    ~Projectile();

    void update() override;
    void createUI() override;
    
private:
    float m_speed;

};


#endif