#ifndef CAMERAFOLLOW_H
#define CAMERAFOLLOW_H

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "../engineClass/gameObject.h"
#include "component.h"


class CameraFollow : public Component {
public:

    CameraFollow(float distance = 2.0f, float pitch = 0.35f);
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
    float m_pitch;

    GameObject *m_player;



};

#endif