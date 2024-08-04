#include "core/core.hpp"
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

const int BLINK_WINDOW_WIDTH{ 800 };
const int BLINK_WINDOW_HEIGHT{ 600 };

int main() {
	std::cout << "BLINK.EXE INITIALIZING" << std::endl;
	if (!glfwInit()) {
		std::cout << "GLFW countn't start" << std::endl;
		return -1;
	}
	GLFWwindow* window{ glfwCreateWindow(BLINK_WINDOW_WIDTH, BLINK_WINDOW_HEIGHT, "BLINK", nullptr, nullptr) };
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return -1;
	}

	glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}