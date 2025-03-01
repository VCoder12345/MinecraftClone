#include "BlockFactory.h"

#include <game/Game.h>

#include <map>

void BlockFactory::init() {
	ResourceManager& rm = Game::instance().getResourceManager();
	std::map<std::string, int> textureMap;

	std::string textureNames[] = {
		"smooth_stone", "dirt",
		"furnace_top", "furnace_side",
		"furnace_front", "grass_block_side", "grass_top", "stone"
	};

	int counter = 0;
	for (std::string texName : textureNames) {
		Texture tex = rm.loadTexture("dirt", ("assets/sprites/block/" + texName + ".png").c_str(), true, true);
		textureMap[texName] = counter;
		textures.push_back(tex);
		++counter;
	}

	for (int i = 0; i < 5; ++i) {
		materials.push_back(nullptr);
	}


	materials[MAT_SMOOTH_STONE] = new Material(textureMap["smooth_stone"]);
	materials[MAT_DIRT] = new Material(textureMap["dirt"]);
	materials[MAT_FURNACE]
		= new Material(textureMap["furnace_side"], textureMap["furnace_side"], textureMap["furnace_top"], textureMap["furnace_top"], textureMap["furnace_front"], textureMap["furnace_side"]);
	materials[MAT_STONE] = new Material(textureMap["stone"]);
	materials[MAT_GRASS_DIRT] = new Material(textureMap["grass_block_side"], textureMap["grass_top"], textureMap["dirt"]);
	
}

Block* BlockFactory::createBlock(int type) {
	return new Block(materials[type]);
}