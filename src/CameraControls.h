#pragma once

#include <glm/glm.hpp>

#include "InputHandler.h"
#include "Camera.h"
#include "Clock.h"
#include "utils.h"

class MoveCameraHandler : public IKeyHandler {
	private:
		Camera& _camera;
		const Clock& _clock;
		const utils::Direction _moveDirection;

	public:
		MoveCameraHandler(Camera& camera, const Clock& clock, const utils::Direction moveDirection);
		void whilePressed() override;
};


class RotateCameraHandler : public IMouseMoveHandler {
	private:
		Camera& _camera;
		const Clock& _clock;

	public:
		RotateCameraHandler(Camera& camera, const Clock& clock);
		void onMouseMoved(int deltaX, int deltaY);
};
