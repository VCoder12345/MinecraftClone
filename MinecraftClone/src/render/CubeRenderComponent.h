#pragma once

#include <ecs/Component.h>

class CubeRenderComponent : public Component {
public:
	glm::vec3 color;
	Texture texture;
	float opacity;

	CubeRenderComponent(Texture texture, glm::vec3 color, float opacity = 1.0f) : texture(texture), color(color), opacity(opacity) {}
};