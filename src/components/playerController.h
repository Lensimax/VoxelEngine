#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "component.h"

class PlayerController : public Component {
public:
    PlayerController();
    void inputUpdate() override;
    void createUI() override;
    
private:
    float m_jumpForce;

};

#endif