#ifndef THIRDPERSONCONTROLLER_H
#define THIRDPERSONCONTROLLER_H

#include "component.h"
#include "cameraProjective.h"
#include "../engineClass/gameObject.h"

class ThirdPersonController : public Component {
public:
    ThirdPersonController();
    ~ThirdPersonController();

    void update() override;
    void createUI() override;

    void setCamera(GameObject *camera){m_camera = camera;}


private:

    GameObject *m_camera;
    glm::vec2 m_sensitivity;

};


#endif