#pragma once

#include "Renderer.h"
#include "ShaderManager.h"
#include "InputHandler.h"
#include "Camera.h"
#include "Clock.h"

#include <GLFW/glfw3.h>

class Game {

	private:
		Camera* _camera;
		Renderer* _renderer;
		ShaderManager* _shaderManager;
		InputHandler* _inputHandler;

		GLFWwindow* _window;

		Clock* _clock;
		bool _isRunning;
		GLuint _vertexArrayID;

	public:
		Game(GLFWwindow* window);
		~Game();

		void start();
		void end();
};
