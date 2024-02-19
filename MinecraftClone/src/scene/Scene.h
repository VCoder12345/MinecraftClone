#pragma once

#include <vector>

#include <ecs/System.h>
#include <ecs/Entity.h>

class Scene : public IUpdateable {
public:
	std::vector<Entity*> entities;
	std::vector<System*> systems;

	Scene();
	~Scene();


	void addEntity(Entity* entity);
	void addSystem(System* system);

	void removeEntity(Entity* entity);


	//update methods
	void onStart();

	void onPreUpdate();
	void onUpdate();
	void onLateUpdate();

	void onPhysics();

	void onRender();

	//to be overwritten by different scene-classes; here the entities and systems get instantiated
	virtual void prepare() = 0;
	virtual Entity& getCamera() = 0;




};