#ifndef LIGHT_H
#define LIGHT_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

#include "../../engineObject.h"

class Light : public EngineObject {

    public:
        virtual glm::vec3 getLight() = 0;

        float intensity;
    protected:
};

#endif
