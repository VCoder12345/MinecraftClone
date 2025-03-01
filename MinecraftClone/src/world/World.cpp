#include "World.h"
#include <thread>

void World::init() {
	//currentChunk->genMesh(quadCulling);
}

void World::setChunk(unsigned int i, unsigned int j, unsigned int k, Chunk* chunk) {
	std::lock_guard<std::mutex> lock(_m);
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

void World::genBorderI(unsigned int i) {
	std::thread th(&World::genBorderIT, this, i);
	th.detach();
}

void World::genBorderJ(unsigned int j) {
	std::thread th(&World::genBorderIT, this, j);
	th.detach();
}

void World::genBorderK(unsigned int k) {
	std::thread th(&World::genBorderIT, this, k);
	th.detach();
}

void World::genBorderIT(unsigned int i) {
	for (int j = 0; j < chunkStoreSizeHor; ++j) {
		for (int k = 0; k < chunkStoreSizeVer; ++k) {
			setChunk(i, j, k, createChunk(i, j, k));
		}
	}
}

void World::genBorderJT(unsigned int j) {
	for (int i = 0; i < chunkStoreSizeHor; ++i) {
		for (int k = 0; k < chunkStoreSizeVer; ++k) {
			setChunk(i, j, k, createChunk(i, j, k));
		}
	}
}

void World::genBorderKT(unsigned int k) {
	for (int j = 0; j < chunkStoreSizeHor; ++j) {
		for (int i = 0; i < chunkStoreSizeHor; ++i) {
			setChunk(i, j, k, createChunk(i, j, k));
		}
	}
}

void World::createChunkThread(unsigned int i, unsigned int j, unsigned int k) {
	Chunk* chunk = createChunk(i, j, k);

	setChunk(i, j, k, chunk);
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