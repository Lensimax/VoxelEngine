#ifndef CHUNK_H
#define CHUNK_H

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "../tools/lights/light.h"
#include "mesh/mesh.h"

#include "../material/material.h"

#include <array>

template<class T, size_t N>
using ChunkGrid = std::array<std::array<std::array<T, N>, N>, N>;

class Chunk {

public:
    Chunk(float size);
    ~Chunk();

	void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light, Mesh *mesh, Material *material);

    void setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light, Material *material);

    bool getCell(unsigned int i, unsigned int j, unsigned int k);

private:

	void createChunk();



    float sizeOfOneCube;
    ChunkGrid<bool, 16> grid;
};


#endif