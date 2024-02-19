#include "World.h"

void World::init() {
	//currentChunk->genMesh(quadCulling);
}

void World::setChunk(unsigned int i, unsigned int j, Chunk* chunk) {
	chunks[chunkIndex(i, j)] = chunk;
}

Chunk* World::getChunk(unsigned int i, unsigned int j) {
	return chunks[chunkIndex(i, j)];
}

Chunk* World::createChunk(int i, int j) {
	Chunk* chunk = new Chunk(chunkSize, blFactory);
	worldGenerator.initChunk(chunk, i + shiftx, j + shifty);
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

	if (y < 0 || y >= chunkSize) {
		info.outOfBounds = true;
		return info;
	}

	int middle = currentChunkIndex();
	int cx = middle;
	int cy = middle;
	while (cx >= 0 && cx < chunkStoreSize && cy >= 0 && cy < chunkStoreSize) {
		if (x < 0) {
			x += chunkSize;
			cx--;
		}
		else if (x >= chunkSize) {
			x -= chunkSize;
			cx++;
		}else if (z < 0) {
			z += chunkSize;
			cy--;
		}
		else if (z >= chunkSize) {
			z -= chunkSize;
			cy++;
		}
		else {
			info.chunk = chunkIndex(cx, cy);
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