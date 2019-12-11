#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "component.h"
#include "../tools/lights/light.h"
#include "../material/lambertian.h"



class MeshRenderer : public Component {

public:

    MeshRenderer();
    ~MeshRenderer();

    virtual void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light);

    virtual void createUI() override;

protected:

    void setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light);

    Material *m_material = NULL;

};

#endif