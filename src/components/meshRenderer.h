#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "renderer.h"
#include "../models/mesh/mesh.h"
#include "../material/lambertian.h"

class MeshRenderer : public Renderer {

public:

	Mesh *mesh = nullptr;
    Material *material = nullptr;

    MeshRenderer();

    void start() override;
    void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;
    void createUI() override;

protected:

    void drawBoxWithMatrices(glm::vec3 min, glm::vec3 max, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat);

    bool m_showBoundingBox;
};

#endif