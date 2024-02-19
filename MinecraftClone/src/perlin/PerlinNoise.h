#pragma once
class PerlinNoise
{
public:
	PerlinNoise(unsigned int seed);

	float noise(float x, float y, float z);
	float grad(int hash, float x, float y, float z);
	float fade(float t);
	float lerp(float a, float b, float t);
	float fractalBrownianMotion(float x, float y, float z, int numOctaves);

private:
	int perm[512];
};

