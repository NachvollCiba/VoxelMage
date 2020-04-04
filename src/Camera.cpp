#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(float fieldOfView, float range, float aspectRatio) : 
	_position(glm::vec3(0.0f, 0.0f, 0.0f)),
	_fieldOfView(fieldOfView),
	_nearDepth(0.1f),
	_farDepth(range),
	_aspectRatio(aspectRatio),
	_horizontalAngle(3.14f),
	_verticalAngle(0)
{
	this->_update();
}

void Camera::_update() {
	static const float PI_2 = 3.141592f / 2.0f;

	this->_front = glm::vec3(
	  cos(this->_verticalAngle) * sin(this->_horizontalAngle),
	  sin(this->_verticalAngle),
	  cos(this->_verticalAngle) * cos(this->_horizontalAngle)
	);
	this->_right =
	 glm::vec3(sin(this->_horizontalAngle-PI_2), 0, cos(this->_horizontalAngle-PI_2));
	glm::vec3 up = glm::cross(this->_right, this->_front);

	// recompute the view matrix
	this->_projectionMatrix = 
	 glm::perspective(this->_fieldOfView, this->_aspectRatio, this->_nearDepth, this->_farDepth);
	this->_viewMatrix =
	 glm::lookAt(this->_position, this->_position+this->_front, up);
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


void Camera::setHorizontalAngle(float a) {
	this->_horizontalAngle = a;
	this->_update();
}
void Camera::updateHorizontalAngle(float deltaA) {
	this->_horizontalAngle += deltaA;
	this->_update();
}
void Camera::setVerticalAngle(float a) {
	this->_verticalAngle = a;
	this->_update();
}
void Camera::updateVerticalAngle(float deltaA) {
	this->_verticalAngle += deltaA;
	this->_update();
}


const glm::mat4& Camera::getProjectionMatrix() const { 
	return this->_projectionMatrix;
}
const glm::mat4& Camera::getViewMatrix() const {
	return this->_viewMatrix;
}
const glm::vec3& Camera::getFront() const {
	return this->_front;
}
const glm::vec3& Camera::getRight() const {
	return this->_right;
}


glm::mat4 Camera::transform(const glm::mat4& modelMatrix) const {
	return this->_projectionMatrix * this->_viewMatrix * modelMatrix;
}
