#include <cmath>

#include "terrainChunk.h"
#include "simplexNoise.h"

///////////////////////// Chunk

//// Constructors

TerrainChunk::TerrainChunk(size_t cubic_size, float x, float y, float z) : CubicArray<Voxel>(cubic_size), x(x), y(y), z(z) {
	generate();
}

void TerrainChunk::generate()
{
	float scale = 100.f;
	size_t octaves = 8;

	SimplexNoise snoise(1.0f / scale);

	for(size_t i = 0 ; i < this->width() ; ++i) {
		for(size_t k = 0 ; k < this->depth() ; ++k) {
			
			// perlin_value in [0, 1]
			float perlin_value = (snoise.fractal(octaves,
				                 float(i) + float(this->x) * float(this->width()), 
				                 float(k) + float(this->z) * float(this->depth())) + 1.0) / 2.0;
			
			float max_y = std::round(perlin_value * this->cubic_size());

			// (*this)(i, max_y, k) = Voxel::Full;
			
			for (size_t j = 0 ; j < max_y ; ++j) // => active les voxel de 0 à Y 
			{
				(*this)(i, j, k) = Voxel::Full;
			}
		}
	}
}
