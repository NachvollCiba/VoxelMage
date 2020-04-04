#include "Clock.h"

#include <GLFW/glfw3.h>


Clock::Clock() {
	this->_lastFrameTime = glfwGetTime();
	this->_deltaFrameTime = 0;
}

void Clock::_update() {
	double thisFrameTime = glfwGetTime();
	this->_deltaFrameTime = thisFrameTime - this->_lastFrameTime;
	this->_lastFrameTime = thisFrameTime;
}

float Clock::getDeltaFrameTime() const {
	return this->_deltaFrameTime;
}
