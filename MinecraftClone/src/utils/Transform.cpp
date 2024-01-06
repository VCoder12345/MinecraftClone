#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform(glm::vec3 pos, glm::vec3 size) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, size);
}