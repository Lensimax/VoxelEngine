#ifndef _TERRAIN_CHUNK_H_
#define _TERRAIN_CHUNK_H_

#include <glm/glm.hpp>

#include "cubicArray.h"
#include "voxel.h"
#include "../models/mesh/mesh.h"

struct TerrainChunk : public CubicArray<Voxel> {

	glm::vec3 position;

	/// Constructors

	TerrainChunk(size_t cubic_size, const glm::vec3& pos); // Initialise les valeurs du chunk à partir de sa position dans le monde
	TerrainChunk(size_t cubic_size, float x, float y, float z);

	/// Modificators

	void generate(); // regenère le chunk en fonction de ça position dans le monde

	/// Mesh Création

	// Renvoie 6 booleen correspondant à la presence ou non des 6 voisins du voxel (x, y, z)
	std::array<bool, 6> surrounding(size_t x, size_t y, size_t z) const;
		
	void addCubeFaces(Mesh* mesh, const std::array<bool, 6>& surrounding, size_t x, size_t y, size_t z) const;
	
	Mesh* calculateMesh() const;
};

#endif