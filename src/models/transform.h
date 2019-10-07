#ifndef TRANSFORM_H
#define TRANSFORM_H


#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Transform {
    public:
        Transform(vec3 center = vec3(0.0,0.0,0.0), vec3 position = vec3(0.0,0.0,0.0), vec3 scale = vec3(1.0,1.0,1.0), vec3 rotation = vec3(0.0,0.0,0.0));
        ~Transform();

        void setPosition(vec3 position);
        void rotate(vec3 angle);
        void scale(vec3 scale);
        void setCenter(vec3 center);

        mat4 getMat4();

        void createUI();

    private:

        vec3 vecPosition, vecScale, vecRotation, center;



};

#endif
