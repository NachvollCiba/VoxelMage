#pragma once

#include <glm/glm.hpp>

#include "InputHandler.h"
#include "Camera.h"
#include "utils.h"

class MoveCameraHandler : public IKeyHandler {
	private:
		Camera& _camera;
		glm::vec3 _direction;

	public:
		MoveCameraHandler(Camera& camera, utils::Direction moveDirection);
		void whilePressed() override;
};
