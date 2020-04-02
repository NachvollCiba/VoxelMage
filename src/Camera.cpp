#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(float fieldOfView, float range, float aspectRatio) : 
	_position(glm::vec3(0.0f, 0.0f, 0.0f)),
	_direction(glm::vec3(0.0f, 0.0f, 0.0f)),
	_fieldOfView(fieldOfView),
	_nearDepth(0.1f),
	_farDepth(range),
	_aspectRatio(aspectRatio)
{
	this->_update();
}

void Camera::_update() {
	static const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);

	// recompute the view matrix
	this->_projectionMatrix = 
	 glm::perspective(this->_fieldOfView, this->_aspectRatio, this->_nearDepth, this->_farDepth);
	this->_viewMatrix = glm::lookAt(this->_position, this->_direction, UP);
}

void Camera::setPosition(float x, float y, float z) {
	this->setPosition(glm::vec3(x, y, z));
}
void Camera::setPosition(const glm::vec3& newPosition) {
	this->_position = newPosition;
	this->_update();
}
void Camera::updatePosition(float dX, float dY, float dZ) {
	this->updatePosition(glm::vec3(dX, dY, dZ));
}
void Camera::updatePosition(const glm::vec3& delta) {
	this->_position += delta;
	this->_update();
}


void Camera::setDirection(float x, float y, float z) {
	this->setDirection(glm::vec3(x, y, z));
}
void Camera::setDirection(const glm::vec3& newDirection) {
	this->_direction = newDirection;
	this->_update();
}
void Camera::updateDirection(float x, float y, float z) {
	this->updateDirection(glm::vec3(x, y, z));
}
void Camera::updateDirection(const glm::vec3& delta) {
	this->_direction += delta;
	this->_update();
}


const glm::mat4& Camera::getProjectionMatrix() const { 
	return this->_projectionMatrix;
}
const glm::mat4& Camera::getViewMatrix() const {
	return this->_viewMatrix;
}


glm::mat4 Camera::transform(const glm::mat4& modelMatrix) const {
	return this->_projectionMatrix * this->_viewMatrix * modelMatrix;
}
