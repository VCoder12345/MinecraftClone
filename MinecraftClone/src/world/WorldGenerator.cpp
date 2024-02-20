#include "WorldGenerator.h"

WorldGenerator::WorldGenerator() : perlin(200) {
	
}

void WorldGenerator::initChunk(Chunk* chunk, int i, int j, int g) {
	for (int x = 0; x < chunk->size; ++x) {
		for (int y = 0; y < chunk->size; ++y) {
			int h;
			if (g < 0) {
				h = chunk->size;
			}
			else {
				float r = (perlin.fractalBrownianMotion((float)x / chunk->size + i, (float)y / chunk->size + j, 0.0f, 6) + 1) / 2;
				
				h = (int)(r * 38) - g * chunk->size;

				if (h > chunk->size) {
					h = chunk->size;
				}
			}
			
			for (int z = 0; z < h; ++z) {
				chunk->setBlock(MAT_DIRT, x, y, z);
			}
		}
	}
}