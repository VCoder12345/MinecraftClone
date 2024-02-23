#pragma once
#include <world/World.h>

class Globals
{
public:
	static World& getWorld() {
		return *world;
	}

	static void provideWorld(World* world) {
		Globals::world = world;
	}

	static void deleteWorld() {
		delete world;
	}

private:
	static World* world;
};

std::ostream& operator<<(std::ostream& os, const glm::vec3& v);

