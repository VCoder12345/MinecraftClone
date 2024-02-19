#pragma once

#include <render/Texture.h>
#include <ecs/Component.h>
#include <block/Material.h>

static const int FRONT_FACE = 0;
static const int BACK_FACE = 1;
static const int LEFT_FACE = 2;
static const int RIGHT_FACE = 3;
static const int TOP_FACE = 4;
static const int BOTTOM_FACE = 5;

class Block : public Component {
public:
	Material* material;

	Block(Material* material) : material(material) {}
};