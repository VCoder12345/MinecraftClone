#pragma once

#include <world/Chunk.h>
#include <block/BlockFactory.h>
#include <world/WorldGenerator.h>

#include <vector>
#include <mutex>


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
	BlockFactory* blFactory;
	const int chunkSize;
	Chunk** chunks;
	const int chunkStoreSizeHor;
	const int chunkStoreSizeVer;
	const int chunkVisualDistHor;
	const int chunkVisualDistVer;
	int shiftx = 0, shiftz = 0;
	int yOffset = 0;
	WorldGenerator worldGenerator;
	Selection slc;
	bool quadCulling = true;

	World(int chunkStoreSizeHor, int chunkStoreSizeVer,  const int chunkVisualDistHor, const int chunkVisualDistVer, const int chunkSize)
		: chunkStoreSizeHor(chunkStoreSizeHor), chunkStoreSizeVer(chunkStoreSizeVer), chunkVisualDistHor(chunkVisualDistHor), chunkVisualDistVer(chunkVisualDistVer), chunkSize(chunkSize), worldGenerator(200) {
		blFactory = new BlockFactory();
		chunks = new Chunk * [chunkStoreSizeHor * chunkStoreSizeHor * chunkStoreSizeVer];

		for (int i = 0; i < chunkStoreSizeHor; ++i) {
			for (int j = 0; j < chunkStoreSizeHor; ++j) {
				for (int k = 0; k < chunkStoreSizeVer; ++k) {
					int index = chunkIndex(i, j, k);
					chunks[index] = createChunk(i, j, k);
				}
			}
		}
	}

	~World() {
		delete blFactory;

		for (int i = 0; i < chunkStoreSizeHor * chunkStoreSizeHor * chunkStoreSizeVer; ++i) {
			delete chunks[i];
		}

		delete chunks;
	}

	int middleHor() {
		return chunkStoreSizeHor / 2;
	}

	int middleVer() {
		return chunkStoreSizeVer / 2;
	}

	void init();
	Chunk* getChunk(unsigned int i, unsigned int j, unsigned int k);
	void setChunk(unsigned int i, unsigned int j, unsigned int k, Chunk* chunk);
	Chunk* createChunk(int i, int j, int k);
	bool inBounds(int x, int y, int z);
	BlockInfo getBlockInfo(int i, int j, int k);
	int chunkIndex(unsigned int i, unsigned int j, unsigned int k) {
		return (k * chunkStoreSizeHor * chunkStoreSizeHor) + (j * chunkStoreSizeHor) + i;
	}

	std::vector<Texture>& textures() {
		return blFactory->textures;
	}
	void genBorderI(unsigned int i);
	void genBorderJ(unsigned int j);
	void genBorderK(unsigned int k);



private:
	std::mutex _m;
	void genBorderIT(unsigned int i);
	void genBorderJT(unsigned int j);
	void genBorderKT(unsigned int k);
};

