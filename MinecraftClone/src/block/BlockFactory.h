#pragma once

#include <vector>
#include <render/Texture.h>
#include <block/Material.h>
#include <block/Block.h>

static const int MAT_SMOOTH_STONE = 0;
static const int MAT_DIRT = 1;
static const int MAT_FURNACE = 2;
static const int MAT_STONE = 3;
static const int MAT_GRASS_DIRT = 4;


class BlockFactory
{
public:
	std::vector<Texture> textures;

	BlockFactory() {
		init();
	}

	~BlockFactory() {
		for (Material* mat : materials) {
			delete mat;
		}
	}

	void init();
	Block* createBlock(int type);

private:
	std::vector<Material*> materials;
};

