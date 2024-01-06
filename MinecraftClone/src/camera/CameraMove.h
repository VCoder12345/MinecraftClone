#pragma once

#include <ecs/Component.h>
#include <glm/glm.hpp> 

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.1f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class CameraMove : public Component {
public:
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	glm::vec3 pos;
	
	float yaw;
	float pitch;
	float speed;
	float upSpeed;
	float sensitivity;
	float zoom;
	
	glm::vec2 moldPos;

	CameraMove(glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), upSpeed(SPEED * 0.6f), sensitivity(SENSITIVITY), zoom(ZOOM) {
		this->pos = pos;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
	}
};