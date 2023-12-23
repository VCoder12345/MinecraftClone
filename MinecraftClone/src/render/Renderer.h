#pragma once

#include <ecs/System.h>

#include <glm/glm.hpp>

#include <window/Window.h>

#include <glad/glad.h>

#include "Shader.h"

class Renderer : public System {
public:
	Renderer(Shader shader);

protected:
	Window& window;
	glm::mat4 projection;
	Shader shader;
};