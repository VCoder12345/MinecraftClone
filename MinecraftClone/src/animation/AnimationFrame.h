#pragma once

#include <render/Texture.h>

class AnimationFrame {
public:
	Texture texture;

	AnimationFrame(Texture texture) : texture(texture) {}
};