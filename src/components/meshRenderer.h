#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "../engineClass/component.h"
#include "../tools/lights/light.h"
#include "../material/material.h"

class MeshRenderer {

public:

    MeshRenderer();
    ~MeshRenderer();

    void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light);

protected:

    void setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light);

    Material *m_material;

};

#endif