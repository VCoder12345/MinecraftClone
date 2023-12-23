#pragma once

#include <scene/Scene.h>

class ProbeScene : public Scene {
public:
	Entity* camera;

	void prepare();
	Entity& getCamera();
};