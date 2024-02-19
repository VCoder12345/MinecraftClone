#include "CameraSystem.h"

#include <ecs/EntityItr.h>
#include <debug/Log.h>
#include <globals/Globals.h>

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
	if (input.getControlValue("close")) {
		Game::instance().close();
	}
	Time& time = Game::instance().getTime();
	World& world = Globals::getWorld();
	for (Entity& e : EntityItr<CameraMove>()) {
		CameraMove& cm = e.getComponent<CameraMove>();
		Transform& t = e.getComponent<Transform>();

		float velocity = cm.speed;

		float forwardVal = -input.getControlValue("forward");
		float sideVal = input.getControlValue("side");

		cm.pos += cm.front * velocity * forwardVal;
		cm.pos += cm.right * velocity * sideVal;

		if (input.getControlValue("up")) {
			cm.pos.y += cm.upSpeed;
		}

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

		int x = (int)cm.pos.x;
		int z = (int)cm.pos.z;
	
		if (x >= world.chunkSize) {
			//std::cout << "left shift" << std::endl;
			//shift window to the left
			for (int i = 0; i < world.chunkStoreSize; ++i) {
				for (int j = 0; j < world.chunkStoreSize; ++j) {
					if (i == world.chunkStoreSize - 1) {
						world.setChunk(i, j, world.createChunk(i, j));
					}
					else {
						world.setChunk(i, j, world.getChunk(i + 1, j));
					}
				}
			}
			world.shiftx++;
			cm.pos.x -= world.chunkSize;
		}
		else if (x < 0) {
			//std::cout << "right shift" << std::endl;
			//shift window to the right
			for (int i = world.chunkStoreSize - 1; i >= 0; --i) {
				for (int j = 0; j < world.chunkStoreSize; ++j) {
					if (i == 0) {
						world.setChunk(i, j, world.createChunk(i, j));
					}
					else {
						world.setChunk(i, j, world.getChunk(i - 1, j));
					}
				}
			}
			world.shiftx++;
			cm.pos.x += world.chunkSize;
		}

		if (z >= world.chunkSize) {
			//std::cout << "front shift" << std::endl;
			for (int j = 0; j < world.chunkStoreSize; ++j) {
				for (int i = 0; i < world.chunkStoreSize; ++i) {
					if (j == world.chunkStoreSize - 1) {
						world.setChunk(i, j, world.createChunk(i, j));
					}
					else {
						world.setChunk(i, j, world.getChunk(i, j + 1));
					}
				}
			}
			
			world.shifty++;
			cm.pos.z -= world.chunkSize;
		}
		else if (z < 0) {
			//std::cout << "back shift" << std::endl;
			for (int j = world.chunkStoreSize - 1; j >= 0; --j) {
				for (int i = 0; i < world.chunkStoreSize; ++i) {
					if (j == 0) {
						world.setChunk(i, j, world.createChunk(i, j));
					}
					else {
						world.setChunk(i, j, world.getChunk(i, j - 1));
					}
				}
			}
			world.shifty++;
			cm.pos.z += world.chunkSize;
		}

		//std::cout << cm.pos.x << " " << cm.pos.z << std::endl;
	}

}
