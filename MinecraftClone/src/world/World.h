#pragma once

#include <world/Chunk.h>
#include <block/BlockFactory.h>
#include <world/WorldGenerator.h>

#include <vector>


struct BlockInfo {
	bool outOfBounds;
	bool hit;
	int chunk;
	int i, j, k;
};



struct Selection {
	BlockInfo info;
	int glI, glJ, glK;
	int face;
};


class World
{
public:
	Chunk* currentChunk;
	bool quadCulling = true;
	BlockFactory* blFactory;
	const int chunkSize;
	Chunk** chunks;
	const int chunkStoreSize;
	const int chunkVisualDist;
	int shiftx = 0, shifty = 0;
	WorldGenerator worldGenerator;
	Selection slc;

	World(const int chunkStoreSize, const int chunkVisualDist, const int chunkSize)
		: chunkStoreSize(chunkStoreSize), chunkVisualDist(chunkVisualDist), chunkSize(chunkSize){
		blFactory = new BlockFactory();
		chunks = new Chunk * [chunkStoreSize * chunkStoreSize];

		for (int i = 0; i < chunkStoreSize; ++i) {
			for (int j = 0; j < chunkStoreSize; ++j) {
				int index = chunkIndex(i, j);
				chunks[index] = createChunk(i, j);
				//chunks[index]->genMesh(true);
			}
		}

		int middle = currentChunkIndex();
		currentChunk = getChunk(middle, middle);
	}

	~World() {
		delete blFactory;

		for (int i = 0; i < chunkStoreSize * chunkStoreSize; ++i) {
			delete chunks[i];
		}

		delete chunks;
	}

	int currentChunkIndex() {
		return chunkStoreSize / 2;
	}

	void init();
	Chunk* getChunk(unsigned int i, unsigned int j);
	void setChunk(unsigned int i, unsigned int j, Chunk* chunk);
	Chunk* createChunk(int i, int j);
	bool inBounds(int x, int y, int z);
	BlockInfo getBlockInfo(int i, int j, int k);
	int chunkIndex(unsigned int i, unsigned int j) {
		return j * chunkStoreSize + i;
	}

	std::vector<Texture>& textures() {
		return blFactory->textures;
	}
};

