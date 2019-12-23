#ifndef _TERRAIN_CHUNK_H_
#define _TERRAIN_CHUNK_H_

#include "cubicArray.h"
#include "voxel.h"

struct TerrainChunk : public CubicArray<Voxel> {

public:	

	float x, y, z;

	/// Constructors

	TerrainChunk(size_t cubic_size, float x, float y, float z); // Initialise les valeurs du chunk à partir de sa position dans le monde

	/// Modificators

	void generate(); // regenère le chunk en fonction de ça position dans le monde
};

#endif