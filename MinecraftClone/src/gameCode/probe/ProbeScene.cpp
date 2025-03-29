#include "ProbeScene.h"



#include <input/Controls.h>

#include <game/Game.h>
#include <utils/Transform.h>
#include <render/CubeRenderComponent.h>
#include <render/CubeRenderer.h>
#include <input/Controls.h>
#include <camera/CameraMove.h>
#include <camera/CameraSystem.h>
#include <block/BlockRenderer.h>
#include <block/Block.h>
#include <world/World.h>
#include <globals/Globals.h>
#include <player/BlockPicker.h>
#include <player/BlockPickSystem.h>

void ProbeScene::prepare() {
	ResourceManager& rm = Game::instance().getResourceManager();

	//Shader cubeShader = rm.loadShader("cubeShader", "assets/shaders/cubeShader.vert", "assets/shaders/cubeShader.frag");
	//Shader blockInstaceShader = rm.loadShader("blockInstaceShader", "assets/shaders/blockInstanceShader.vert", "assets/shaders/blockInstanceShader.frag");
	Shader blockShader = rm.loadShader("blockShader", "assets/shaders/blockShader.vert", "assets/shaders/blockShader.frag");
	Shader slcBlockShader = rm.loadShader("slcBlockShader", "assets/shaders/slcShader.vert", "assets/shaders/slcShader.frag");
	Shader debugCubeShader = rm.loadShader("debugCubeShader", "assets/shaders/debugCubeShader.vert", "assets/shaders/slcShader.frag");
	//Texture dirtTex = rm.loadTexture("dirt", "assets/sprites/block/dirt.png", true, true);
	//Texture sandstoneTex = rm.loadTexture("sandstone", "assets/sprites/block/sandstone.png", true, true);


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

	GroupControl* downControl = new GroupControl();
	downControl->addControl(new KeyControl(GLFW_KEY_LEFT_SHIFT));
	input.addControl(downControl, "down");

	GroupControl* closeControl = new GroupControl();
	closeControl->addControl(new JButtonControl(JOYSTICK_START));
	closeControl->addControl(new KeyControl(GLFW_KEY_ESCAPE));
	input.addControl(closeControl, "close");

	
	World* world = new World(7, 7, 3, 3, 16);
	Globals::provideWorld(world);

	camera = new Entity("Camera");
	camera->addComponent(new Transform(glm::mat4(1.0f)));
	camera->addComponent(new CameraMove(glm::vec3(0, 0, 0)));
	camera->addComponent(new BlockPicker(20));
	addEntity(camera);

	addSystem(new CameraSystem());
	//addSystem(new BlockInstanceRenderer(blockInstaceShader));
	addSystem(new BlockRenderer(blockShader, slcBlockShader, debugCubeShader, true));
	addSystem(new BlockPickSystem());
	
}

ProbeScene::~ProbeScene() {
	Globals::deleteWorld();
}

Entity& ProbeScene::getCamera() {
	return *camera;
}