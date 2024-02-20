#pragma once

#include <world/Chunk.h>
#include <perlin/PerlinNoise.h>

class WorldGenerator
{
public:
	WorldGenerator();
	void initChunk(Chunk* chunk, int i, int j, int g);

private:
	PerlinNoise perlin;
};

