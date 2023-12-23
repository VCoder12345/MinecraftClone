#pragma once

class IUpdateable {
public:
	virtual void onStart() = 0;

	virtual void onPreUpdate() = 0;
	virtual void onUpdate() = 0;
	virtual void onLateUpdate() = 0;
	
	virtual void onPhysics() = 0;

	virtual void onRender() = 0;
};