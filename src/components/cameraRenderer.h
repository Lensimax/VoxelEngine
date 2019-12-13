#ifndef CAMERA_RENDERER_H
#define CAMERA_RENDERER_H

#include "meshRenderer.h"

#include "../tools/camera.h"

class CameraRenderer : public MeshRenderer {
public:
    CameraRenderer();
    ~CameraRenderer();

    virtual void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light);

    virtual void createUI() override;

private:
    float m_lineLength = 0.2f;

    Camera *m_cam;

};

#endif