#ifndef CAMERAFOLLOW_H
#define CAMERAFOLLOW_H


#include "../engineClass/gameObject.h"
#include "component.h"
class CameraFollow : public Component {
public:

    CameraFollow(float distance = 6.3f, float offsetAngle = 0.0f);
    ~CameraFollow();

    void update() override;
    void createUI() override;

    void setPlayer(GameObject *player){m_player = player;}
    GameObject *getPlayer(){return m_player;}

private:

    float getHorizontalDistance();
    float getVerticalDistance();
    void updateCameraPositionFromPlayer();

    float m_distanceFromPlayer;
    float m_angleOffset;

    GameObject *m_player;



};

#endif