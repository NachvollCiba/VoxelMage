#pragma once

#include <glm/glm.hpp>

#include "InputHandler.h"
#include "Camera.h"
#include "utils.h"

class MoveCameraHandler : public IKeyHandler {
	private:
		Camera& _camera;
		const utils::Direction _moveDirection;

	public:
		MoveCameraHandler(Camera& camera, utils::Direction moveDirection);
		void whilePressed() override;
};


class RotateCameraHandler : public IMouseMoveHandler {
	private:
		Camera& _camera;

	public:
		RotateCameraHandler(Camera& camera);
		void onMouseMoved(int deltaX, int deltaY);
};
