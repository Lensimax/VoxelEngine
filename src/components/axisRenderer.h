#ifndef AXIS_RENDERER_H
#define AXIS_RENDERER_H

#include "renderer.h"


class AxisRenderer : public Renderer {

public:
    
    AxisRenderer();

    void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;

    void createUI() override;

private:

    float m_lineLength;
    float m_lineWidth;
};

#endif