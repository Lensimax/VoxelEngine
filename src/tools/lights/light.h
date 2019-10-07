#ifndef LIGHT_H
#define LIGHT_H


#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "../../engineObject.h"

class Light : public EngineObject {

    public:
        virtual glm::vec3 getLight() = 0;

        float intensity;
    protected:
};

#endif
