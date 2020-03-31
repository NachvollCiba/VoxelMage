#include <exception>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "InputHandler.h"


GLFWwindow* createWindow() {
	// initialize GLFW
	if (!glfwInit()) {
		throw "Failed to initialize glfw3";
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "VoxelMage", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "FATAL ERROR: could not create GLFW Window");
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	glewExperimental=true;
	if (glewInit() != GLEW_OK) {
		throw "Failed to initialize GLEW";
	}

	return window;
}

int main(int argc, char *argv[]) {
	GLFWwindow* window = createWindow();

	InputHandler input = InputHandler(*window);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (!input.isKeyPressed(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(window) == 0);

	return 0;
}

