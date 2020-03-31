#include "InputHandler.h"
InputHandler::InputHandler(GLFWwindow& window)
	: window(window) {

	glfwSetInputMode(&window, GLFW_STICKY_KEYS, GL_TRUE);
}

bool InputHandler::isKeyPressed(int key) {
	return glfwGetKey(&this->window, key) == GLFW_PRESS;
}
