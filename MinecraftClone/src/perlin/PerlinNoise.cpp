#include "PerlinNoise.h"

#include <algorithm>
#include <random>
#include <iostream>

float PerlinNoise::lerp(float a, float b, float t) {
	return a + t * (b - a);
}

float PerlinNoise::fade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

PerlinNoise::PerlinNoise(unsigned int seed) {
	for (int i = 0; i < 256; ++i) {
		perm[i] = i;
	}

	//shuffle perm
	std::shuffle(perm, perm + 256, std::default_random_engine(seed));

	for (int i = 256; i < 512; ++i) {
		perm[i] = perm[i - 256];
	}
}

float PerlinNoise::grad(int hash, float x, float y, float z) {
	switch (hash & 0xF) {
	case 0x0: return  x + y;
	case 0x1: return -x + y;
	case 0x2: return  x - y;
	case 0x3: return -x - y;
	case 0x4: return  x + z;
	case 0x5: return -x + z;
	case 0x6: return  x - z;
	case 0x7: return -x - z;
	case 0x8: return  y + z;
	case 0x9: return -y + z;
	case 0xA: return  y - z;
	case 0xB: return -y - z;
	case 0xC: return  y + x;
	case 0xD: return -y + z;
	case 0xE: return  y - x;
	case 0xF: return -y - z;
	}

	return 0;

	/*int h = hash & 15;
	double u = h < 8 ? x : y;
	double v;

	if (h < 4) {
		v = y;
	}
	else if (h == 12 || h == 14) {
		v = x;
	}
	else {
		v = z;
	}

	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);*/
}

float PerlinNoise::noise(float x, float y, float z) {
	int xi = (int)x & 255;
	int yi = (int)y & 255;
	int zi = (int)z & 255;
	float xf = x - (int)x;
	float yf = y - (int)y;
	float zf = z - (int)z;
	float u = fade(xf);
	float v = fade(yf);
	float w = fade(zf);

	int aaa = perm[perm[perm[xi] + yi] + zi];
	int aba = perm[perm[perm[xi] + yi + 1] + zi];
	int aab = perm[perm[perm[xi] + yi] + zi + 1];
	int abb = perm[perm[perm[xi] + yi + 1] + zi + 1];
	int baa = perm[perm[perm[xi + 1] + yi] + zi];
	int bba = perm[perm[perm[xi + 1] + yi + 1] + zi];
	int bab = perm[perm[perm[xi + 1] + yi] + zi + 1];
	int bbb = perm[perm[perm[xi + 1] + yi + 1] + zi + 1];

	float x1 = lerp(grad(aaa, xf, yf, zf), grad(baa, xf - 1, yf, zf), u);
	float x2 = lerp(grad(aba, xf, yf - 1, zf), grad(bba, xf - 1, yf - 1, zf), u);
	float y1 = lerp(x1, x2, v);

	x1 = lerp(grad(aab, xf, yf, zf - 1), grad(bab, xf - 1, yf, zf - 1), u);
	x2 = lerp(grad(abb, xf, yf - 1, zf - 1), grad(bbb, xf - 1, yf - 1, zf - 1), u);
	float y2 = lerp(x1, x2, v);

	return lerp(y1, y2, w);
}

float PerlinNoise::fractalBrownianMotion(float x, float y, float z, int numOctaves) {
	float result = 0;
	float amplitude = 1.0f;
	float freq = 1;
	float total = 0;
	for (int oct = 0; oct < numOctaves; ++oct) {
		float n = amplitude * noise(x * freq, y * freq, z * freq);
		result += n;

		amplitude *= 0.5f;
		freq *= 2.0f;
		total += amplitude;
	}

	return result / total;
}