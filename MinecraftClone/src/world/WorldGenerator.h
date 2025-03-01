#pragma once

#include <world/Chunk.h>
#include <perlin/PerlinNoise.h>

class WorldGenerator
{
public:
	WorldGenerator(unsigned int seed);
	void initChunk(Chunk* chunk, int i, int j, int g);

private:
	unsigned int seed;
	PerlinNoise perlin;
};

