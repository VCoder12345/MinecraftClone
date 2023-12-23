#include "Game.h"

const float MS_PER_UPDATE = 1.0f / 80.0f;

Game::Game() {
	init();
}

Game::~Game() {
	//delete services
	delete log;
	delete resourceManager;
	delete time;
	delete eventBus;
	delete input;
	delete window;

	//delete scenes
	for (const auto& kv : scenes) {
		delete kv.second;
	}
}

void Game::init() {
	//init services
	window = new Window(1920, 1080, "M1n3cr4ft", false, true);
	log = new Log();
	resourceManager = new ResourceManager();
	//renderer = new Renderer(*window);
	time = new Time();
	eventBus = new EventBus();
	input = new Input(window->window);
	
}

void Game::addScene(Scene* scene, unsigned int id) {
	scenes[id] = scene;
	if (currentScene == NULL)
		loadScene(id);
}

void Game::loadScene(unsigned int id) {
	currentScene = scenes[id];
}



void Game::start() {
	currentScene->onStart();

	int frames = 0;
	int updates = 0;
	float secs = 0;
	float previousTime = glfwGetTime();
	float lag = 0.0f;

	while (!window->shouldClose()) {
		float currentTime = glfwGetTime();
		float elapsed = currentTime - previousTime;
		previousTime = currentTime;
		lag += elapsed;

		

		while (lag >= MS_PER_UPDATE) {
			update();
			lag -= MS_PER_UPDATE;
		}

		if (fpsDisplay) {
			secs += elapsed;
			if (secs >= 1.0f) {
				secs -= 1.0f;

				getLog().log("FPS: ", frames);

				frames = 0;
			}
			frames++;

		}
		

		window->clear();

		currentScene->onRender();

		window->update();

		
	}

	window->terminate();
}

void Game::update() {
	currentScene->onPreUpdate();
	currentScene->onUpdate();
	currentScene->onLateUpdate();

	currentScene->onPhysics();
}

void Game::close() {
	window->close();
}