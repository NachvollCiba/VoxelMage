#include "InputHandler.h"

#include <algorithm>


InputHandler::InputHandler(GLFWwindow& window) :
	_window(window),
	_registeredKeys(std::vector<int>()),
	_mouseMovementHandlers(std::vector<IMouseMoveHandler*>())
{
	glfwSetInputMode(&window, GLFW_STICKY_KEYS, GL_TRUE);
}

void InputHandler::update() {
	// call all KeyHandlers
	for (int& key : this->_registeredKeys) {
		IKeyHandler* handler = this->_keyHandlers[key];
		bool isPressed = this->_isKeyPressed(key);

		if (isPressed) {
			this->_prevKeyState[key] ? handler->whilePressed() : handler->onJustPressed();
		} else {
			this->_prevKeyState[key] ? handler->whileReleased() : handler->onJustReleased();
		}

		this->_prevKeyState[key] = isPressed;
	}

	// find the center of the window
	int windowWidth, windowHeight;
	glfwGetWindowSize(&this->_window, &windowWidth, &windowHeight);
	int centerX = windowWidth/2;
	int centerY = windowHeight/2;
	
	// call all the mouse movement handlers
	double mouseX, mouseY;
	glfwGetCursorPos(&this->_window, &mouseX, &mouseY);
	if ((int)mouseX != centerX && (int)mouseY != centerY) {
		for (IMouseMoveHandler* mouseHandler : this->_mouseMovementHandlers) {
			mouseHandler->onMouseMoved(mouseX-centerX, mouseY-centerY);
		}
		glfwSetCursorPos(&this->_window, centerX, centerY);
	}
}

void InputHandler::registerKeyHandler(int key, IKeyHandler* handler) {
	if (std::find(this->_registeredKeys.begin(), this->_registeredKeys.end(), key) == this->_registeredKeys.end()) {
		this->_registeredKeys.push_back(key);
	}
	this->_keyHandlers[key] = handler;
}

void InputHandler::unregisterKeyHandler(int key) {
	// remove the key from the list of registered keys
	std::vector<int>::iterator position = 
	 std::find(this->_registeredKeys.begin(), this->_registeredKeys.end(), key);

	if (position != this->_registeredKeys.end()) {
		this->_registeredKeys.erase(position);
	}
}

void InputHandler::registerMouseMovementHandler(IMouseMoveHandler* handler) {
	this->_mouseMovementHandlers.push_back(handler);
}

void InputHandler::unregisterMouseMovementHandler(IMouseMoveHandler* handler) {
	std::vector<IMouseMoveHandler*>::iterator position =
	 std::find(this->_mouseMovementHandlers.begin(), this->_mouseMovementHandlers.end(), handler);

	if (position != this->_mouseMovementHandlers.end()) {
		this->_mouseMovementHandlers.erase(position);
	}
}


bool InputHandler::_isKeyPressed(int key) {
	return glfwGetKey(&this->_window, key) == GLFW_PRESS;
}
