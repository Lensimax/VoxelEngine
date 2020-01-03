#ifndef AXIS_RENDERER_H
#define AXIS_RENDERER_H

#include "meshRenderer.h"


class AxisRenderer : public MeshRenderer {
public:
    AxisRenderer();
    ~AxisRenderer();

    virtual void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light);

    virtual void createUI() override;

private:
    float m_lineLength;
    float m_lineWidth;

};

#endif