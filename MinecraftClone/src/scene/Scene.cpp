#include "Scene.h"


Scene::Scene() {}

Scene::~Scene() {
	for (Entity* e : entities) {
		delete e;
	}

	for (System* s : systems) {
		delete s;
	}
}

void Scene::addEntity(Entity* entity) {
	entities.push_back(entity);
}

void Scene::addSystem(System* system) {
	systems.push_back(system);
}

void Scene::onStart() {
	prepare();
	for (System* s : systems) {
		s->onStart();
	}
}

void Scene::onPreUpdate() {
	for (System* s : systems) {
		s->onPreUpdate();
	}
}

void Scene::onUpdate() {
	for (System* s : systems) {
		s->onUpdate();
	}
}

void Scene::onLateUpdate() {
	for (System* s : systems) {
		s->onLateUpdate();
	}
}

void Scene::onPhysics() {
	for (System* s : systems) {
		s->onPhysics();
	}
}

void Scene::onRender() {
	for (System* s : systems) {
		s->onRender();
	}
}

