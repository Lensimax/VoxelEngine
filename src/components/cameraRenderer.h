#ifndef CAMERARENDERER_H
#define CAMERARENDERER_H

#include "meshRenderer.h"

class CameraRenderer : public MeshRenderer {
public:

    CameraRenderer();
    ~CameraRenderer();

    virtual void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light);

    virtual void createUI() override;

private:
    float m_lineLength;
    float m_lineWidth;

    const glm::vec4 m_colorLine = glm::vec4(0.8,0.8,0.8,1);
};


#endif