#include "CameraSystem.h"

#include <ecs/EntityItr.h>
#include <debug/Log.h>

void CameraSystem::onStart() {
	Input& input = Game::instance().getInput();
	for (Entity& e : EntityItr<CameraMove>()) {
		CameraMove& cm = e.getComponent<CameraMove>();
		Transform& t = e.getComponent<Transform>();

		updateCamVectors(cm, t);
		cm.moldPos = input.getMousePos();

	}
}

void CameraSystem::updateCamVectors(CameraMove& cm, Transform& t) {
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(cm.yaw)) * cos(glm::radians(cm.pitch));
	newFront.y = sin(glm::radians(cm.pitch));
	newFront.z = sin(glm::radians(cm.yaw)) * cos(glm::radians(cm.pitch));

	cm.front = glm::normalize(newFront);
	cm.right = glm::normalize(glm::cross(cm.front, cm.worldUp));
	cm.up = glm::normalize(glm::cross(cm.right, cm.front));

	t.model = glm::lookAt(cm.pos, cm.pos + cm.front, cm.up);
}


void CameraSystem::onUpdate() {
	Input& input = Game::instance().getInput();
	if (input.isKeyPressed(GLFW_KEY_ESCAPE)) {
		Game::instance().close();
	}
	Time& time = Game::instance().getTime();
	for (Entity& e : EntityItr<CameraMove>()) {
		CameraMove& cm = e.getComponent<CameraMove>();
		Transform& t = e.getComponent<Transform>();

		float velocity = cm.speed;

		float forwardVal = input.getControlValue("forward");
		float sideVal = input.getControlValue("side");

		
		

		cm.pos += cm.front * velocity * forwardVal;
		cm.pos += cm.right * velocity * sideVal;

		glm::vec2 mpos = input.getMousePos();

		glm::vec2 offset = mpos - cm.moldPos;
		offset *= cm.sensitivity;

		cm.yaw += offset.x;
		cm.pitch -= offset.y;

		if (cm.pitch > 89.0f) {
			cm.pitch = 89.0f;
		}
		else if (cm.pitch < -89.0f) {
			cm.pitch = -89.0f;
		}

		updateCamVectors(cm, t);

		cm.moldPos = mpos;
	}
}
