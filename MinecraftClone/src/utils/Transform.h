#pragma once

#include <ecs/Component.h>

#include <glm/glm.hpp> 

class Transform : public Component {
public:
	glm::mat4 model;

	Transform(glm::mat4 model) : model(model) {}
};
