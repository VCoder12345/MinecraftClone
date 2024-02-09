#include "ProbeScene.h"



#include <input/Controls.h>

#include <game/Game.h>
#include <utils/Transform.h>
#include <render/CubeRenderComponent.h>
#include <render/CubeRenderer.h>
#include <input/Controls.h>
#include <camera/CameraMove.h>
#include <camera/CameraSystem.h>
#include <block/BlockInstanceRenderer.h>
#include <block/BlockRenderer.h>
#include <block/Block.h>

void ProbeScene::prepare() {
	ResourceManager& rm = Game::instance().getResourceManager();

	//Shader cubeShader = rm.loadShader("cubeShader", "assets/shaders/cubeShader.vert", "assets/shaders/cubeShader.frag");
	//Shader blockInstaceShader = rm.loadShader("blockInstaceShader", "assets/shaders/blockInstanceShader.vert", "assets/shaders/blockInstanceShader.frag");
	Shader blockShader = rm.loadShader("blockShader", "assets/shaders/blockShader.vert", "assets/shaders/blockShader.frag");
	Texture dirtTex = rm.loadTexture("dirt", "assets/sprites/block/dirt.png", true, true);
	Texture sandstoneTex = rm.loadTexture("sandstone", "assets/sprites/block/sandstone.png", true, true);


	//controls
	Input& input = Game::instance().getInput();

	GroupControl* forwardControl = new GroupControl();
	forwardControl->addControl(new JAxisControl(JOYSTICK_FORWARD_AXIS));
	forwardControl->addControl(new KeyControl(GLFW_KEY_W, -1.0f));
	forwardControl->addControl(new KeyControl(GLFW_KEY_S, 1.0f));
	input.addControl(forwardControl, "forward");

	GroupControl* sideControl = new GroupControl();
	sideControl->addControl(new JAxisControl(JOYSTICK_SIDE_AXIS));
	sideControl->addControl(new KeyControl(GLFW_KEY_A, -1.0f));
	sideControl->addControl(new KeyControl(GLFW_KEY_D, 1.0f));
	input.addControl(sideControl, "side");

	GroupControl* upControl = new GroupControl();
	upControl->addControl(new JButtonControl(JOYSTICK_A));
	upControl->addControl(new KeyControl(GLFW_KEY_SPACE));
	input.addControl(upControl, "up");

	GroupControl* closeControl = new GroupControl();
	closeControl->addControl(new JButtonControl(JOYSTICK_START));
	closeControl->addControl(new KeyControl(GLFW_KEY_ESCAPE));
	input.addControl(closeControl, "close");

	for (int h = 0; h < 3; ++h) {
		for (int i = 0; i < 30; ++i) {
			for (int j = 0; j < 30; ++j) {
				Entity* cube1 = new Entity("Cube1");
				glm::mat4 cmodel1(1.0f);

				float x = -i;
				float y = -j;
				cmodel1 = glm::translate(cmodel1, glm::vec3(-i, h, -j));

				cube1->addComponent(new Transform(cmodel1));

				if (i % 2 == j % 2 && i % 2 == h % 2) {
					cube1->addComponent(new Block(sandstoneTex));
				}
				else {
					cube1->addComponent(new Block(dirtTex));
				}

				//cube1->addComponent(new CubeRenderComponent(playerTex, glm::vec3(1.0f)));

				addEntity(cube1);
			}
		}
	}
	

	

	camera = new Entity("Camera");
	camera->addComponent(new Transform(glm::mat4(1.0f)));
	camera->addComponent(new CameraMove(glm::vec3(0, 0, 0)));
	addEntity(camera);

	addSystem(new CameraSystem());
	//addSystem(new BlockInstanceRenderer(blockInstaceShader));
	addSystem(new BlockRenderer(blockShader));
	
}

Entity& ProbeScene::getCamera() {
	return *camera;
}