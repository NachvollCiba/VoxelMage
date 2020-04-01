#include "InputHandler.h"

#include <algorithm>


InputHandler::InputHandler(GLFWwindow& window) :
	_window(window),
	_registered(std::vector<int>())
{
	glfwSetInputMode(&window, GLFW_STICKY_KEYS, GL_TRUE);
}

void InputHandler::update() {
	for (int& key : this->_registered) {
		IKeyHandler* handler = this->_handlers[key];
		bool isPressed = this->_isKeyPressed(key);

		if (isPressed) {
			this->_prevState[key] ? handler->whilePressed() : handler->onJustPressed();
		} else {
			this->_prevState[key] ? handler->whileReleased() : handler->onJustReleased();
		}

		this->_prevState[key] = isPressed;
	}
}

void InputHandler::registerKeyHandler(int key, IKeyHandler* handler) {
	if (std::find(this->_registered.begin(), this->_registered.end(), key) == this->_registered.end()) {
		this->_registered.push_back(key);
	}
	this->_handlers[key] = handler;
}

void InputHandler::unregisterKeyHandler(int key) {
	// remove the key from the list of registered keys
	std::vector<int>::iterator position = 
	 std::find(this->_registered.begin(), this->_registered.end(), key);

	if (position != this->_registered.end()) {
		this->_registered.erase(position);
	}
}


bool InputHandler::_isKeyPressed(int key) {
	return glfwGetKey(&this->_window, key) == GLFW_PRESS;
}
