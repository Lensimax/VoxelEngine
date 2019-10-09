

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
	Grid(unsigned int size = 16, float width = 1, float z = 0);
	~Grid();
private:



};




#endif
