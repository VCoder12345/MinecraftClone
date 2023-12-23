#pragma once

#include "Event.h"

class HandlerFunctionBase {
public:
	void exec(Event* event) {
		call(event);
	}

private:
	virtual void call(Event* event) = 0;
};