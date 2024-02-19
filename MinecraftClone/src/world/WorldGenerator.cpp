#include "WorldGenerator.h"

WorldGenerator::WorldGenerator() : perlin(200) {
	
}

void WorldGenerator::initChunk(Chunk* chunk, int i, int j) {
	for (int x = 0; x < chunk->size; ++x) {
		for (int y = 0; y < chunk->size; ++y) {
			float r = (perlin.fractalBrownianMotion((float)x / chunk->size + i, (float)y / chunk->size + j, 0.0f, 6) + 1) / 2;
			//std::cout << r << std::endl;
			int h = (int)(r * 16);
			for (int z = 0; z < h; ++z) {
				chunk->setBlock(MAT_STONE, x, y, z);
			}
		}
	}

	/*for (int x = 0; x < 16; ++x) {
		for (int y = 0; y < 16; ++y) {
			for (int z = 15; z >= 0; --z) {
				float r = perlin.fractalBrownianMotion(x / 16.0f, y / 16.0f, z / 16.0f, 4);
				if (r >= 0) {
					for (int h = z; h >= 0; --h) {
						chunk->setBlock(MAT_DIRT, x, y, h);
					}
					break;
				}
			}
		}
	}*/
}