#include "ProbeScene.h"



#include <input/Controls.h>

#include <game/Game.h>
#include <utils/Transform.h>
#include <render/CubeRenderComponent.h>
#include <render/CubeRenderer.h>
#include <input/Controls.h>
#include <camera/CameraMove.h>
#include <camera/CameraSystem.h>

void ProbeScene::prepare() {
	ResourceManager& rm = Game::instance().getResourceManager();

	Shader cubeShader = rm.loadShader("cubeShader", "assets/shaders/cubeShader.vert", "assets/shaders/cubeShader.frag");
	Texture playerTex = rm.loadTexture("dirt", "assets/sprites/block/dirt.png", true, true);


	//controls
	Input& input = Game::instance().getInput();

	GroupControl* forwardControl = new GroupControl();
	forwardControl->addControl(new JAxisControl(1));
	forwardControl->addControl(new KeyControl(GLFW_KEY_W, 1.0f));
	forwardControl->addControl(new KeyControl(GLFW_KEY_S, -1.0f));
	input.addControl(forwardControl, "forward");

	GroupControl* sideControl = new GroupControl();
	sideControl->addControl(new JAxisControl(0));
	sideControl->addControl(new KeyControl(GLFW_KEY_A, -1.0f));
	sideControl->addControl(new KeyControl(GLFW_KEY_D, 1.0f));
	input.addControl(sideControl, "side");

	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 30; ++j) {
			Entity* cube1 = new Entity("Cube1");
			glm::mat4 cmodel1(1.0f);

			float x = -i;
			float y = -j;
			cmodel1 = glm::translate(cmodel1, glm::vec3(-i, 0.0f, -j));

			cube1->addComponent(new Transform(cmodel1));
			cube1->addComponent(new CubeRenderComponent(playerTex, glm::vec3(0.7f)));

			addEntity(cube1);
		}
	}

	

	camera = new Entity("Camera");
	camera->addComponent(new Transform(glm::mat4(1.0f)));
	camera->addComponent(new CameraMove(glm::vec3(0, 0, 0)));
	addEntity(camera);

	addSystem(new CameraSystem());
	addSystem(new CubeRenderer(cubeShader));
}

Entity& ProbeScene::getCamera() {
	return *camera;
}