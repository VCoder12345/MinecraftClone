#pragma once

#include "Control.h"

#include <vector>

class KeyControl : public Control {
public:
	KeyControl(int key, int pressValue = 1.0f) : key(key), pressValue(pressValue) {}

	float getValue();

private:
	int key;
	int pressValue;
};

class JButtonControl : public Control {
public:
	JButtonControl(int button, int pressValue = 1.0f) : button(button), pressValue(pressValue) {}

	float getValue();

private:
	int button;
	int pressValue;

};

class JAxisControl : public Control {
public:
	JAxisControl(int axis) : axis(axis) {}

	float getValue();

private:
	int axis;
};

class GroupControl : public Control {
public:
	GroupControl() {}

	void addControl(Control* control);

	float getValue();

private:
	std::vector<Control*> controls;
};