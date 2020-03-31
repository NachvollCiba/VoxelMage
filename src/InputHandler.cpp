#include "InputHandler.h"
InputHandler::InputHandler(GLFWwindow& window)
	: window(window) {

}

bool InputHandler::isKeyPressed(int key) {
	return glfwGetKey(&this->window, key) == GLFW_PRESS;
}
