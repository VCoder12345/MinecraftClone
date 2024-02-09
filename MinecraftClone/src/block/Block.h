#pragma once

#include <render/Texture.h>
#include <ecs/Component.h>

class Block : public Component {
public:
	Texture texture;

	Block(Texture texture) : texture(texture){}
};