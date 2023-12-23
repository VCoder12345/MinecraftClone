#pragma once

#include "IUpdateable.h"

class System : public IUpdateable {
public:
	virtual void onStart() {}

	virtual void onPreUpdate() {}
	virtual void onUpdate() {}
	virtual void onLateUpdate() {}

	virtual void onPhysics() {}

	virtual void onRender() {}
};