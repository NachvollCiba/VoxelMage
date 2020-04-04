#include "CameraControls.h"
#include "utils.h"

#define SPEED 0.5f
#define MOUSE_SPEED 0.1f

MoveCameraHandler::MoveCameraHandler(Camera& camera, utils::Direction moveDirection) :
	_camera(camera), _moveDirection(moveDirection)
{
}

void MoveCameraHandler::whilePressed() {
	switch (this->_moveDirection) {
		case(utils::FORWARD):
			this->_camera.updatePosition(this->_camera.getFront()*SPEED);
			break;
		case(utils::BACKWARD):
			this->_camera.updatePosition(-this->_camera.getFront()*SPEED);
			break;
		case(utils::RIGHT):
			this->_camera.updatePosition(this->_camera.getRight()*SPEED);
			break;
		case(utils::LEFT):
			this->_camera.updatePosition(-this->_camera.getRight()*SPEED);
			break;
	}
}



RotateCameraHandler::RotateCameraHandler(Camera& camera) : _camera(camera) {

}

void RotateCameraHandler::onMouseMoved(int deltaX, int deltaY) {
	this->_camera.updateVerticalAngle(deltaX * MOUSE_SPEED);
	this->_camera.updateHorizontalAngle(deltaY * MOUSE_SPEED);
}
