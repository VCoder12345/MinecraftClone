#include "Window.h"

#include <game/Game.h>

Window::Window(int width, int height, const char* title, bool fullscreen, bool lockmouse) {
	//init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	create(width, height, title, fullscreen, lockmouse);
}

Window::~Window() {
	delete window;
}

void Window::create(int width, int height, const char* title, bool fullscreen, bool lockmouse) {
	this->width = width;
	this->height = height;

	GLFWmonitor* monitor = NULL;
	if (fullscreen)
		monitor = glfwGetPrimaryMonitor();
	window = glfwCreateWindow(width, height, title, monitor, NULL);
	if (window == NULL)
	{
		//log.log("Failed to create GLFW window");
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});

	if(lockmouse)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSwapInterval(0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//log.log("Failed to initialize GLAD");
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::clear() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::terminate() {
	glfwTerminate();
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::close() {
	glfwSetWindowShouldClose(window, true);
}