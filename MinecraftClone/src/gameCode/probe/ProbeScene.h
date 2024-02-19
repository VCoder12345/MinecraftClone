#pragma once

#include <scene/Scene.h>

class ProbeScene : public Scene {
public:
	~ProbeScene();
	Entity* camera;

	void prepare();
	Entity& getCamera();
};