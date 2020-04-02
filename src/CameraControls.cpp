#include "CameraControls.h"

#define SPEED 0.5f;

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

