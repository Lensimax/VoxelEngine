#ifndef TRANSFORM_H
#define TRANSFORM_H


#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

using namespace glm;

class Transform {
    public:
        Transform(vec3 center = vec3(0.0,0.0,0.0), vec3 position = vec3(0.0,0.0,0.0), vec3 scale = vec3(1.0,1.0,1.0), vec3 rotation = vec3(0.0,0.0,0.0));
        ~Transform();

        void setPosition(vec3 position);
        void setRotation(vec3 angle);
        void rotatefromScreen(vec2 v);
        void scale(vec3 scale);
        void setCenter(vec3 center);

        void addTranslation(vec3 t);
        void addTranslationAfter(vec3 t);

        vec3 getPosition();
        vec3 getRotation();
        vec3 getScale();

        void update();

        virtual mat4 getModelMat(mat4 modelMat = glm::mat4(1));
        mat4 getModelToChild(mat4 modelMat);

        void createUI();

        void setAnimation(bool b_X, bool b_Y, bool b_Z, float SpeedX = 0.01f, float SpeedY = 0.01f, float SpeedZ = 0.01f);
        void setChildAnimation(bool b_X, bool b_Y, bool b_Z, float SpeedX = 0.01f, float SpeedY = 0.01f, float SpeedZ = 0.01f);
        void setSameAsParent(bool position, bool rotation);


        void decompose(mat4 mat);

    protected:

        vec3 rotationMatrixToEulerAngles(mat4 r);

        void reset();

        vec3 m_position, m_scale, m_rotation, m_center, m_translateAfter;

        bool m_samePosition, m_sameRotation;

        vec3 m_positionToSend, m_scaleToSend, m_rotationToSend;


        // To animate the transform
        float m_animRotX, m_animRotY, m_animRotZ;
        float m_animChildRotX, m_animChildRotY, m_animChildRotZ;

        float m_animRotSpeedX, m_animRotSpeedY, m_animRotSpeedZ;
        float m_animChildRotSpeedX, m_animChildRotSpeedY, m_animChildRotSpeedZ;

        bool m_b_animRotX = false, m_b_animRotY = false, b_animRotZ = false;
        bool m_b_animChildRotX, m_b_animChildRotY, m_b_animChildRotZ;

        const float m_defaultSpeed = 0.01;

        glm::mat4 m_test = glm::mat4(1);
};

#endif
