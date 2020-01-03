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
#include "mesh/meshCube.h"

#include "../material/material.h"

#include <array>


///////////////////////// Voxel


// using Voxel = bool;

struct Voxel {
	
	enum class Type : unsigned char {
		Empty,
		Full
	};

	Type type;

	//// Constructors

	Voxel();
	Voxel(Voxel::Type type);

	//// Cast operators 

	operator bool() const;
};


///////////////////////// CubicGrid


template<class T, size_t N>
struct CubicGrid : public std::array<T, N * N * N>
{
	//// Accessors

	constexpr size_t width()  const;
	constexpr size_t height() const;
	constexpr size_t depth()  const;
	constexpr size_t borderSize() const;


	// Les coordonnées n'ont pas le droit d'être négatives
	T&       operator()(size_t x, size_t y, size_t z);       // Accès comme un tableau à 3 dimensions
	const T& operator()(size_t x, size_t y, size_t z) const;

	//// Booleans

	bool on_bounds(size_t x, size_t y, size_t z) const;	
};

///////////////////////// Chunk

// world relative coordinate : w_x, w_y, w_z
// chunk relative coordinate : c_x, c_y, c_z

class Chunk : public CubicGrid<Voxel, 128> {

public:	

	//// Constructors

	Chunk(float voxelSize);
	Chunk(float voxelSize, float x, float y, float z); // position dans la grille monde

	//// Accessors

	float voxelSize() const;
	glm::uvec3 dimensions() const;
	
	void generateTerrain(float w_x, float w_y, float w_z);
	size_t getHeight(float w_x, float w_z);

	// bool allNeighborsActivated(size_t x, size_t y, size_t z) const; // min(1, 1, 1), max(14, 14, 14)
	bool surrounded(size_t c_x, size_t c_y, size_t c_z) const; // min(1, 1, 1), max(14, 14, 14)


	// Renvoie 6 booleen correspondant à la presence ou non des 6 voisins du voxel (x, y, z)
	std::array<bool, 6> surrounding(size_t c_x, size_t c_y, size_t c_z) const;
		
	void addCubeFaces(Mesh* mesh, const std::array<bool, 6>& surrounding, size_t c_x, size_t c_y, size_t c_z) const;
	
	void calculateMesh(Mesh* mesh) const;


	//// Drawing / OpenGL

	void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light, Mesh *mesh, Material *material);
	void setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light, Material *material);

private:

	float m_voxelSize;
	size_t m_octaves;
};


#endif