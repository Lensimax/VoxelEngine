#ifndef THIRDPERSONCONTROLLER_H
#define THIRDPERSONCONTROLLER_H

#include "component.h"
#include "cameraProjective.h"

class ThirdPersonController : public Component {
public:
    ThirdPersonController();
    ~ThirdPersonController();



private:

    CameraProjective *m_camera;

};


#endif