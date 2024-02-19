#pragma once

#include <glm/glm.hpp>
#include <map>
#include <string>

#include "Control.h"

const int JOYSTICK_SIDE_AXIS = 0;
const int JOYSTICK_FORWARD_AXIS = 1;
const int JOYSTICK_START = 7;
const int JOYSTICK_A = 0;

class GLFWwindow;

class Input {
public:
	Input(GLFWwindow* window);
	~Input();

	glm::vec2 getMousePos();
	bool isKeyPressed(int key);

	bool isMouseBtnPressed(int btn);
	static void mouse_btn_callback(GLFWwindow* window, int button, int action, int mods);

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