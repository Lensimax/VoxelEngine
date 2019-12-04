#ifndef MESHCUBE_H
#define MESHCUBE_H

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "mesh.h"

class MeshCube : public Mesh {
public:
    MeshCube(float w = 1.0f, bool center = true);
	~MeshCube();

	void recreate() override;
	void createUI();


private:

	void createMesh(float w);
    void createPositions(float w);

    void createNormals();
    void createm_tangents();
    void createUVs();
    void createColors();

    float m_width;
    bool m_centered;

};


#endif