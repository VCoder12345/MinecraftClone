#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window {
public:
	int width, height;
	GLFWwindow* window;

	Window(int width, int height, const char* title, bool fullscreen = false, bool lockmouse = false);
	Window() {}
	~Window();

	void create(int width, int height, const char* title, bool fullscreen, bool lockmouse);

	void clear();
	void update();
	void terminate();
	void close();

	bool shouldClose();

};