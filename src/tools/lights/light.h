#ifndef LIGHT_H
#define LIGHT_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "../../engineObject.h"

class Light : public EngineObject {

    public:
        virtual glm::vec3 getLight() = 0;

        float intensity;
    protected:
};

#endif
