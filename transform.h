#ifndef TRANSFORM_H
#define TRANSFORM_H

#ifndef GLM_H
#define GLM_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#endif

using namespace glm;

class Transform {
    public:
        Transform(vec3 position = vec3(0.0,0.0,0.0), vec3 scale = vec3(1.0,1.0,1.0), vec3 rotation = vec3(0.0,0.0,0.0));
        ~Transform();

        void setPosition(vec3 position);
        void rotate(vec3 angle);
        void scale(vec3 scale);

        mat4 getMat4();

    private:

        vec3 vecPosition, vecScale, vecRotation;



};

#endif
