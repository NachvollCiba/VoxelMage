#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "utils.h"
#include "InputHandler.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "CameraControls.h"
#include "Renderer.h"


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


class CloseGameKeyHandler : public IKeyHandler {
	private: 
		bool* _running;

	public:
		CloseGameKeyHandler(bool* running) : _running(running) {}

		void onJustPressed() override {
			*this->_running = false;
		}
};

void registerKeyHandlers(bool* runningFlag, Camera& camera, InputHandler& input) {
	// Close Game Handler
	CloseGameKeyHandler* closeHandler = new CloseGameKeyHandler(runningFlag);
	input.registerKeyHandler(GLFW_KEY_ESCAPE, closeHandler);
	input.registerKeyHandler(GLFW_KEY_Q, closeHandler);

	// Key Handler for moving the camera
	input.registerKeyHandler(GLFW_KEY_A, new MoveCameraHandler(camera, utils::LEFT));
	input.registerKeyHandler(GLFW_KEY_D, new MoveCameraHandler(camera, utils::RIGHT));
	input.registerKeyHandler(GLFW_KEY_W, new MoveCameraHandler(camera, utils::FORWARD));
	input.registerKeyHandler(GLFW_KEY_S, new MoveCameraHandler(camera, utils::BACKWARD));
}


int main(int argc, char *argv[]) {
	GLFWwindow* window = createWindow();

	InputHandler input = InputHandler(*window);
	ShaderManager shaderManager = ShaderManager("assets/shaders/");

	Camera camera = Camera(45.0f);
	Renderer renderer = Renderer(camera, shaderManager);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	camera.setPosition(4, 3, 3);
	camera.setDirection(0, 0, 0);

	renderer.renderCube(glm::vec3(0.0f, 0.0f, 0.0f));
	renderer.renderCube(glm::vec3(5.0f, 0.0f, 0.0f));
	renderer.renderCube(glm::vec3(0.0f, 3.0f, 0.0f));

	// Close Game Key Handler
	bool running = true;
	registerKeyHandlers(&running, camera, input);

	// Main Game Loop
	std::cout << "Entering main loop" << std::endl;
	while (running) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		input.update();
		renderer.update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "Terminating program..." << std::endl;
	glDeleteVertexArrays(1, &vertexArrayID);
	glfwTerminate();
	return 0;
}

