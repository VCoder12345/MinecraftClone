#pragma once

#include <map>

#include <debug/Log.h>
#include <resource/ResourceManager.h>
#include <time/Time.h>
#include <event/EventBus.h>
#include <input/Input.h>

#include <window/Window.h>

#include <scene/Scene.h>

class Game {
public:
	//singleton function
	static Game& instance() {
		static Game* instance = new Game();
		return *instance;
	}

	Game();

	~Game();

	Log& getLog() {
		return *log;
	}

	ResourceManager& getResourceManager() {
		return *resourceManager;
	}

	//Renderer& getRenderer() {
	//	return *renderer;
	//}

	Scene& getCurrentScene() {
		return *currentScene;
	}

	Time& getTime() {
		return *time;
	}

	EventBus& getEventSystem() {
		return *eventBus;
	}

	Input& getInput() {
		return *input;
	}

	Window& getWindow() {
		return *window;
	}

	void start();
	void update();
	void close();

	//scene functions
	void addScene(Scene* scene, unsigned int id);
	void loadScene(unsigned int id);

private:
	//services
	Window* window;
	Log* log;
	ResourceManager* resourceManager;
	/*Renderer* renderer;*/
	Time* time;
	EventBus* eventBus;
	Input* input;

	bool fpsDisplay = true;

	Scene* currentScene;
	std::map<unsigned int, Scene*> scenes;

	void init();
	
};