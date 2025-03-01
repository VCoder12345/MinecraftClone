#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(unsigned int seed) : seed(seed), perlin(seed) {
	srand(seed);
}

double randDouble() {
	return (double)rand() / RAND_MAX;
}

int randInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void WorldGenerator::initChunk(Chunk* chunk, int i, int j, int g) {
	bool overflow;
	int h;
	for (int x = 0; x < chunk->size; ++x) {
		for (int y = 0; y < chunk->size; ++y) {
			overflow = false;
			if (g < 0) {
				h = chunk->size;
				overflow = true;
			}
			else {
				float r = (perlin.fractalBrownianMotion((float)x / chunk->size + i, (float)y / chunk->size + j, 0.0f, 6) + 1) / 2;

				h = (int)(r * 38) - g * chunk->size;

				if (h > chunk->size) {
					h = chunk->size;
					overflow = true;
				}
			}

			for (int z = 0; z < h; ++z) {
				if (g < 0 || (g == 0 && z < randInt(3, randInt(8, 12)))) {
					chunk->setBlock(MAT_STONE, x, y, z);
				}
				else {
					if (z == h - 1 && !overflow) {
						chunk->setBlock(MAT_GRASS_DIRT, x, y, z);
					}
					else {
						chunk->setBlock(MAT_DIRT, x, y, z);
					}
				}
			}
		}
	}
}