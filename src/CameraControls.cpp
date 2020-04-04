#include "CameraControls.h"

#define SPEED 0.5f
#define MOUSE_SPEED 0.3f

MoveCameraHandler::MoveCameraHandler(Camera& camera, utils::Direction moveDirection) :
	_camera(camera)
{
	switch (moveDirection) {
		case(utils::FORWARD):
			this->_direction = glm::vec3(0.0f, 0.0f, 1.0f);
			break;
		case(utils::BACKWARD):
			this->_direction = glm::vec3(0.0f, 0.0f, -1.0f);
			break;
		case(utils::LEFT):
			this->_direction = glm::vec3(-1.0f, 0.0f, 0.0f);
			break;
		case(utils::RIGHT):
			this->_direction = glm::vec3(1.0f, 0.0f, 0.0f);
			break;
		default:
			this->_direction = glm::vec3(0, 0, 0);
			break;
	}
	this->_direction *= SPEED;
}

void MoveCameraHandler::whilePressed() {
	this->_camera.updatePosition(this->_direction);
}



RotateCameraHandler::RotateCameraHandler(Camera& camera) : _camera(camera) {

}

void RotateCameraHandler::onMouseMoved(int deltaX, int deltaY) {
	this->_camera.updateVerticalAngle(deltaX * MOUSE_SPEED);
	this->_camera.updateHorizontalAngle(deltaY * MOUSE_SPEED);
}
