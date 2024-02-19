#pragma once

#include <world/World.h>
#include <ecs/Component.h>

class BlockPicker : public Component {
public:
	float maxPickDist;

	BlockPicker(float maxPickDist) : maxPickDist(maxPickDist) {}
};