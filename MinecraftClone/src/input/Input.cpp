#include "Input.h"

#include <game/Game.h>

Input::Input(GLFWwindow* window) : window(window) {
	
}

Input::~Input() {
	for (const auto& kv : controls) {
		delete kv.second;
	}
}

glm::vec2 Input::getMousePos() {
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return glm::vec2(xpos, ypos);
}

bool Input::isKeyPressed(int key) {
	int state = glfwGetKey(window, key);
	return state == GLFW_PRESS;
}

const float* Input::getJAxes() {
	int count;
	const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
	return axes;
}

const float Input::getJAxis(int axis) {
	
	if (!joystickPresent(GLFW_JOYSTICK_1))
		return 0.0f;
	return getJAxes()[axis];
}

const float Input::getCutJAxis(int axis) {
	float val = getJAxis(axis);
	if (abs(val) < 0.2f)
		val = 0.0f;
	return val;
}

const unsigned char* Input::getJButtons() {
	int count;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
	return buttons;
}

bool Input::isJButtonPressed(int btn) {
	if (!joystickPresent(GLFW_JOYSTICK_1))
		return false;
	return getJButtons()[btn] == GLFW_PRESS;
}

void Input::addControl(Control* control , std::string name) {
	controls[name] = control;
}

float Input::getControlValue(std::string name) {
	return controls[name]->getValue();
}

int Input::joystickPresent(int joystick) {
	int present = glfwJoystickPresent(joystick);
	return present;
}

void Input::printPressedBtns() {
	int count;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);

	for (int i = 0; i < count; ++i) {
		if (buttons[i] == GLFW_PRESS) {
			std::cout << "B" << i << std::endl;
		}
	}
}

void Input::printUsedAxes() {
	int count;
	const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

	for (int i = 0; i < count; ++i) {
		if (abs(axes[i]) > 0.6f) {
			std::cout << "A" << i << std::endl;
		}
	}
}