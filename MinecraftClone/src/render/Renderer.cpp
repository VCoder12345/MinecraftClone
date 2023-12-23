#include "Renderer.h"

#include <game/Game.h>


Renderer::Renderer(Shader shader) : window(Game::instance().getWindow()), shader(shader) {
	float width = static_cast<float>(window.width);
	float height = static_cast<float>(window.height);
	projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
}
