#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Transform {
    public:
        Transform();
        Transform(vec3 position);
        Transform(vec3 position, vec3 scale);
        ~Transform();

        void setPosition(vec3 position);
        void rotate(vec3 axis, float angle);
        void scale(vec3 scale);

        mat4 getMat4();

    private:

        vec3 vecPosition, vecScale, vecRotation;



};

#endif
