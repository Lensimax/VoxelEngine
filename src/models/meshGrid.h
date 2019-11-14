

#ifndef MESHGRID_H
#define MESHGRID_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "mesh.h"

#include <vector>

class MeshGrid : public Mesh {


public:
	MeshGrid(unsigned int size = 16, float w = 1.0f, float y = 0.0f, float amp = 1, float freq = 5.0, float pers = 0.8, int octaves = 2);
	~MeshGrid();

	void recreate() override;
	void createUI();

private:
	void createMesh(int size, float width, float y);
	void addVertex(unsigned int arrayPos, glm::vec3 pos, glm::vec3 n, glm::vec3 tangent, glm::vec3 col, glm::vec2 uv);
	void cleanup();

	glm::vec3 defaultNormal = glm::vec3(0,1,0);
	glm::vec3 defaultColor = glm::vec3(0,1,0);
	glm::vec3 defaultTangent = glm::vec3(1,0,0);

	int nbPointPerRowColumn = 0;
	float width = 0.0f;
	float gridY = 0.0f;

	// NOISE IN THE MESH
	void applyNoiseModification();

	glm::vec2 hash(glm::vec2 p);
	float gnoise(glm::vec2 p);
	float pnoise(glm::vec2 p,float amplitude,float frequency,float persistence, int nboctaves);
	glm::vec3 normalPoint(glm::vec3 point);

	float amplitude;
	float frequency;
	float persistence;
	int nboctaves;

};





#endif
