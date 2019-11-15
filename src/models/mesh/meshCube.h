#ifndef MESHCUBE_H
#define MESHCUBE_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "mesh.h"

class MeshCube : public Mesh {
public:
    MeshCube(float w);
	~MeshCube();

	void recreate() override;
	void createUI();


private:

	void createMesh(float w);
    void createPositions(float w);
    void createTriangles();
    void createInfo();

    float width;

};


#endif