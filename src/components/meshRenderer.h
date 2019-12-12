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


    void drawQuadWithTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4);
    void drawBoxWithMatrices(glm::vec3 min, glm::vec3 max, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat);

    Material *m_material = NULL;

    bool m_showBoundingBox;
    
};

#endif