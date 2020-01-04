#ifndef RENDERER_H
#define RENDERER_H

#include "component.h"
#include "../tools/lights/light.h"

class Renderer : public Component {

public:

    virtual void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) = 0;
};

#endif