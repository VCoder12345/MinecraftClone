#include "World.h"

void World::init() {
	//currentChunk->genMesh(quadCulling);
}

void World::setChunk(unsigned int i, unsigned int j, unsigned int k, Chunk* chunk) {
	chunks[chunkIndex(i, j, k)] = chunk;
}

Chunk* World::getChunk(unsigned int i, unsigned int j, unsigned int k) {
	return chunks[chunkIndex(i, j, k)];
}

Chunk* World::createChunk(int i, int j, int k) {
	Chunk* chunk = new Chunk(chunkSize, blFactory);
	int x = i + shiftx;
	int y = j + shiftz;
	int g = yOffset - chunkStoreSizeVer / 2 + k;
	worldGenerator.initChunk(chunk, x, y, g);
	chunk->genMesh(quadCulling);
	return chunk;
}

bool World::inBounds(int x, int y, int z) {
	return false;
}

BlockInfo World::getBlockInfo(int i, int j, int k) {
	BlockInfo info;
	info.hit = false;
	info.outOfBounds = false;

	int x = i;
	int y = k;
	int z = j;


	int midHor = middleHor();
	int midVer = middleVer();
	int cx = midHor;
	int cz = midHor;
	int cy = midVer;
	while (cx >= 0 && cx < chunkStoreSizeHor && cz >= 0 && cz < chunkStoreSizeHor && cy >= 0 && cy < chunkStoreSizeVer) {
		if (x < 0) {
			x += chunkSize;
			--cx;
		}
		else if (x >= chunkSize) {
			x -= chunkSize;
			++cx;
		}else if (z < 0) {
			z += chunkSize;
			--cz;
		}
		else if (z >= chunkSize) {
			z -= chunkSize;
			++cz;
		}
		else if (y < 0) {
			y += chunkSize;
			--cy;
		}
		else if (y >= chunkSize) {
			y -= chunkSize;
			++cy;
		}
		else {
			info.chunk = chunkIndex(cx, cz, cy);
			info.i = x;
			info.j = z;
			info.k = y;

			if (chunks[info.chunk]->get(x, z, y) != nullptr) {
				info.hit = true;
			}
			break;


		}
	}

	return info;
}