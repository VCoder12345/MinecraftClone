#include "Controls.h"

#include <game/Game.h>

float KeyControl::getValue() {
	if (Game::instance().getInput().isKeyPressed(key))
		return pressValue;
	else
		return 0.0f;
}

float JButtonControl::getValue() {
	if (Game::instance().getInput().isJButtonPressed(button))
		return pressValue;
	else
		return 0.0f;
}

float JAxisControl::getValue() {
	float value = Game::instance().getInput().getCutJAxis(axis);
	return value;
}

void GroupControl::addControl(Control* control) {
	controls.push_back(control);
}

float GroupControl::getValue() {
	for (Control* control : controls) {
		float value = control->getValue();
		if (abs(value) > 0.0f)
			return value;
	}

	return 0.0f;
}