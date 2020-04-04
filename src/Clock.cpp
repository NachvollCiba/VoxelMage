#include "Clock.h"

#include <GLFW/glfw3.h>


Clock::Clock() {
	this->_lastFrameTime = glfwGetTime();
	this->_deltaFrameTime = 0;
}

void Clock::update() {
	double thisFrameTime = glfwGetTime();
	this->_deltaFrameTime = thisFrameTime - this->_lastFrameTime;
	this->_lastFrameTime = thisFrameTime;
}

double Clock::getDeltaFrameTime() {
	return this->_deltaFrameTime;
}
