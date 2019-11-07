#ifndef TRANSFORM_H
#define TRANSFORM_H

#ifndef GLM_H
#define GLM_H
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
        void rotate(vec3 angle);
        void scale(vec3 scale);
        void setCenter(vec3 center);

        void update();

        mat4 getModelMat();
        mat4 getModelMat(mat4 modelMat);
        mat4 getModelToChild(mat4 modelMat);

        void createUI();

        void setAnimation(bool b_X, bool b_Y, bool b_Z, float SpeedX = 0.01f, float SpeedY = 0.01f, float SpeedZ = 0.01f);
        void setChildAnimation(bool b_X, bool b_Y, bool b_Z, float SpeedX = 0.01f, float SpeedY = 0.01f, float SpeedZ = 0.01f);
        void setSameAsParent(bool position, bool rotation);

    private:

        void reset();

        vec3 vecPosition, vecScale, vecRotation, center;

        bool samePosition, sameRotation;

        vec3 positionToSend, scaleToSend, rotationToSend;


        // To animate the transform
        float animRotX, animRotY, animRotZ;
        float animChildRotX, animChildRotY, animChildRotZ;

        float animRotSpeedX, animRotSpeedY, animRotSpeedZ;
        float animChildRotSpeedX, animChildRotSpeedY, animChildRotSpeedZ;

        bool b_animRotX, b_animRotY, b_animRotZ;
        bool b_animChildRotX, b_animChildRotY, b_animChildRotZ;

        const float defaultSpeed = 0.01;

};

#endif
