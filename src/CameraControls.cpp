#include "CameraControls.h"
#include "utils.h"

#define SPEED 5.0f
#define MOUSE_SPEED 0.75f

MoveCameraHandler::MoveCameraHandler(Camera& camera, const Clock& clock, const utils::Direction moveDirection) :
	_camera(camera), _clock(clock), _moveDirection(moveDirection)
{
}

void MoveCameraHandler::whilePressed() {
	switch (this->_moveDirection) {
		case(utils::FORWARD):
			this->_camera.updatePosition(this->_camera.getFront()*SPEED*this->_clock.getDeltaFrameTime());
			break;
		case(utils::BACKWARD):
			this->_camera.updatePosition(-this->_camera.getFront()*SPEED*this->_clock.getDeltaFrameTime());
			break;
		case(utils::RIGHT):
			this->_camera.updatePosition(this->_camera.getRight()*SPEED*this->_clock.getDeltaFrameTime());
			break;
		case(utils::LEFT):
			this->_camera.updatePosition(-this->_camera.getRight()*SPEED*this->_clock.getDeltaFrameTime());
			break;
	}
}



RotateCameraHandler::RotateCameraHandler(Camera& camera, const Clock& clock) : 
	_camera(camera), _clock(clock) {

}

void RotateCameraHandler::onMouseMoved(int deltaX, int deltaY) {
	this->_camera.updateVerticalAngle(deltaY * MOUSE_SPEED * this->_clock.getDeltaFrameTime());
	this->_camera.updateHorizontalAngle(-deltaX * MOUSE_SPEED* this->_clock.getDeltaFrameTime());
}
