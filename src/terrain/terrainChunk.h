#ifndef _TERRAIN_CHUNK_H_
#define _TERRAIN_CHUNK_H_

#include <glm/glm.hpp>

#include "cubicArray.h"
#include "voxel.h"
#include "../models/mesh/mesh.h"
#include "../components/component.h"
#include "../components/meshRenderer.h"

class TerrainChunk : public Component {

public:

	/// Attributes

	CubicArray<Voxel> voxels;
	MeshRenderer* renderer = nullptr;

	/// Constructors

	TerrainChunk(size_t cubic_size);
	~TerrainChunk();

	/// Overrides

    void start() override;
    // void update() override;
    // void createUI() override;

	/// Modificators

	void generate(); // regenère le chunk en fonction de ça position dans le monde
	void calculateMesh();
	void addCubeFaces(const std::array<bool, 6>& surrounding, size_t x, size_t y, size_t z) const;

	/// Accessors

	// Renvoie 6 booleen correspondant à la presence ou non des 6 voisins du voxel (x, y, z)
	std::array<bool, 6> surrounding(size_t x, size_t y, size_t z) const;

	/// Statics

	static size_t getHeightAt(size_t chunk_size, float x, float z);
};

#endif