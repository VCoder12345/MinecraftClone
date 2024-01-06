#pragma once

#include <ecs/Entity.h>
#include <glm/glm.hpp>
#include "Block.h"
#include <string>
#include <utils/Transform.h>
#include <game/Game.h>

class BlockGrid {
public:
	const int w, h, l;
	const float blockSize;
	Entity** blocks;

	BlockGrid(int w, int h, int l, int blockSize) : w(w), h(h), l(l), blockSize(blockSize) {
		this->blocks = new Entity * [w * h * l];
	}

	int toIndex(int i, int j, int k) const {
		return (k * w * h) + (j * w) + i;
	}

	Entity* get(int i, int j, int k) const {
		return blocks[toIndex(i, j, k)];
	}

	bool isBlockEmpty(int i, int j, int k) const {
		return get(i, j, k) == nullptr;
	}

	glm::vec3 blockPos(int i, int j, int k) const {
		return glm::vec3(i * blockSize, j * blockSize, k * blockSize);
	}

	void addBlock(Block* block, int i, int j, int k) {
		const int index = toIndex(i, j, k);
		Entity* bent = new Entity("block" + std::to_string(index));
		bent->addComponent(new Transform(blockPos(i, j, k), glm::vec3(blockSize)));
		bent->addComponent(block);

		blocks[index] = bent;
		Game::instance().getCurrentScene().addEntity(blocks[index]);
	}

	void deleteBlock(int i, int j, int k) {
		const int index = toIndex(i, j, k);
		
		Game::instance().getCurrentScene().removeEntity(blocks[index]);
	}
};