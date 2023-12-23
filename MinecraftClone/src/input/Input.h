#pragma once

#include <glm/glm.hpp>
#include <map>
#include <string>

#include "Control.h"

class GLFWwindow;

class Input {
public:
	Input(GLFWwindow* window);
	~Input();

	glm::vec2 getMousePos();
	bool isKeyPressed(int key);

	const float* getJAxes();
	const float getJAxis(int axis);
	const float getCutJAxis(int axis);

	const unsigned char* getJButtons();
	bool isJButtonPressed(int btn);

	void addControl(Control* control, std::string name);
	float getControlValue(std::string name);

	int joystickPresent(int joystick);

	//debug functions
	void printPressedBtns();
	void printUsedAxes();

private:
	GLFWwindow* window;
	std::map<std::string, Control*> controls;
};