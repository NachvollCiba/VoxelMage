#include "Game.h"
#include "utils.h"
#include "CameraControls.h"

#include <iostream>


class CloseGameKeyHandler : public IKeyHandler {
	private:
		bool* _isRunning;
	public:
		CloseGameKeyHandler(bool* isRunning) : _isRunning(isRunning) {}
		void onJustPressed() override { *this->_isRunning = false; }
};

Game::Game(GLFWwindow* window) :
	_window(window),
	_isRunning(false)
{
	std::cout << "Game object initialization starting" << std::endl;
	
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glGenVertexArrays(1, &this->_vertexArrayID);
	glBindVertexArray(this->_vertexArrayID);
	glEnable(GL_CULL_FACE);

	this->_camera = new Camera(45.0f);
	this->_shaderManager = new ShaderManager("assets/shaders/");
	this->_renderer = new Renderer(*this->_camera, *this->_shaderManager);
	this->_inputHandler = new InputHandler(this->_window);

	this->_clock = new Clock();

	std::cout << "Game object initialized" << std::endl;
}


void Game::start() {
	this->_camera->setPosition(3, 3, 3);

	// Render 3 cubes for testing
	this->_renderer->renderCube(glm::vec3(0.0f, 0.0f, 0.0f));
	this->_renderer->renderCube(glm::vec3(5.0f, 0.0f, 0.0f));
	this->_renderer->renderCube(glm::vec3(0.0f, 3.0f, 0.0f));

	this->_inputHandler->registerKeyHandler(GLFW_KEY_ESCAPE, new CloseGameKeyHandler(&this->_isRunning));
	this->_inputHandler->registerKeyHandler(GLFW_KEY_Q, new CloseGameKeyHandler(&this->_isRunning));

	// Register Key Handlers for moving
	this->_inputHandler->registerKeyHandler(
	 GLFW_KEY_A, new MoveCameraHandler(*this->_camera, *this->_clock, utils::LEFT));
	this->_inputHandler->registerKeyHandler(
	 GLFW_KEY_D, new MoveCameraHandler(*this->_camera, *this->_clock, utils::RIGHT));
	this->_inputHandler->registerKeyHandler(
	 GLFW_KEY_W, new MoveCameraHandler(*this->_camera, *this->_clock, utils::FORWARD));
	this->_inputHandler->registerKeyHandler(
	 GLFW_KEY_S, new MoveCameraHandler(*this->_camera, *this->_clock, utils::BACKWARD));

	this->_inputHandler->registerMouseMovementHandler(
	 new RotateCameraHandler(*this->_camera, *this->_clock));


	// Main Game Loop
	this->_isRunning = true;
	std::cout << "Staring Main Loop" << std::endl;
	while (this->_isRunning) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->_clock->_update();
		this->_inputHandler->update();
		this->_renderer->update();

		glfwSwapBuffers(this->_window);
		glfwPollEvents();
	}
}


Game::~Game() {
	delete this->_renderer;
	delete this->_shaderManager;
	delete this->_inputHandler;
	delete this->_camera;
	delete this->_clock;

	glDeleteVertexArrays(1, &this->_vertexArrayID);
	glfwTerminate();
}


void Game::end() {
	this->_isRunning = false;
}
