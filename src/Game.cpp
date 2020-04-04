#include "Game.h"
#include "utils.h"
#include "CameraControls.h"


Game::Game(GLFWwindow* window) :
	_camera(Camera(45.0f)),
	_shaderManager("assets/shaders/"),
	_renderer(this->_camera, this->_shaderManager),
	_inputHandler(InputHandler(window)),
	_window(window),
	_isRunning(false)
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glGenVertexArrays(1, &this->_vertexArrayID);
	glBindVertexArray(this->_vertexArrayID);
}


void Game::start() {
	this->_camera.setPosition(3, 3, 3);

	// Render 3 cubes for testing
	this->_renderer.renderCube(glm::vec3(0.0f, 0.0f, 0.0f));
	this->_renderer.renderCube(glm::vec3(5.0f, 0.0f, 0.0f));
	this->_renderer.renderCube(glm::vec3(0.0f, 3.0f, 0.0f));

	// Register Key Handlers for moving
	this->_inputHandler.registerKeyHandler(GLFW_KEY_A, new MoveCameraHandler(this->_camera, utils::LEFT));
	this->_inputHandler.registerKeyHandler(GLFW_KEY_D, new MoveCameraHandler(this->_camera, utils::RIGHT));
	this->_inputHandler.registerKeyHandler(GLFW_KEY_W, new MoveCameraHandler(this->_camera, utils::FORWARD));
	this->_inputHandler.registerKeyHandler(GLFW_KEY_S, new MoveCameraHandler(this->_camera, utils::BACKWARD));

	this->_inputHandler.registerMouseMovementHandler(new RotateCameraHandler(this->_camera));


	// Main Game Loop
	this->_isRunning = true;
	while (this->_isRunning) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->_inputHandler.update();
		this->_renderer.update();

		glfwSwapBuffers(this->_window);
		glfwPollEvents();
	}
}


Game::~Game() {
	glDeleteVertexArrays(1, &this->_vertexArrayID);
	glfwTerminate();
}


void Game::end() {
	this->_isRunning = false;
}
