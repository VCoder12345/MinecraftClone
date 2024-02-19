#pragma once


#include <ecs/Entity.h>
#include <glm/glm.hpp>
#include <block/Block.h>
#include <string>
#include <utils/Transform.h>
#include <game/Game.h>
#include <block/BlockFactory.h>

#include <vector>

struct BlockMesh {
	unsigned int VAO;
	int numTriangles;
};



class Chunk {
public:
	const int size;
	const int totalNumBlocks;
	Block** blocks;
	BlockMesh mesh;
	BlockFactory* blFactory;
	int numBlocks = 0;
	const float topFaceIntensity = 1.0f;
	const float bottomFaceIntensity = 0.5f;
	const float frontFaceIntensity = 0.8f;
	const float backFaceIntensity = 0.8f;
	const float leftFaceIntensity = 0.6f;
	const float rightFaceIntensity = 0.6f;


	Chunk(const int size, BlockFactory* blFactory) : size(size), totalNumBlocks(size * size * size), blFactory(blFactory) {
		this->blocks = new Block * [totalNumBlocks];

		for (int i = 0; i < totalNumBlocks; ++i) {
			blocks[i] = nullptr;
		}

	}

	~Chunk() {
		for (int i = 0; i < totalNumBlocks; ++i) {
			delete blocks[i];
		}
		delete[] blocks;
	}

	int toIndex(int i, int j, int k) const;

	Block* get(int i, int j, int k) const;

	bool isBlockEmpty(int i, int j, int k) const;

	glm::vec3 blockPos(int i, int j, int k) const;

	bool isEnclosed(int i, int j, int k);

	void setBlock(int type, int i, int j, int k);

	void deleteBlock(int i, int j, int k);

	BlockMesh& getMesh();

	void genMesh(bool quadCulling);
};