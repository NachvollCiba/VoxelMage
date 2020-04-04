#pragma once

#include <glm/glm.hpp>

#define ASPECT_16_9 16.0f/9.0f
#define ASPECT_4_3 4.0f/3.0f

class Camera {

	private:
		glm::vec3 _position;
		glm::vec3 _front;
		glm::vec3 _right;
		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;

		// rotation
		float _horizontalAngle;
		float _verticalAngle;

		float _fieldOfView; // fov in degrees
		float _aspectRatio;

		float _nearDepth;
		float _farDepth;

		void _update();

	public:
		Camera(float fieldOfView, float range=100.0f, float aspectRatio=ASPECT_4_3);

		void setPosition(float x, float y, float z);
		void setPosition(const glm::vec3& newPosition);
		void updatePosition(float dX, float dY, float dZ);
		void updatePosition(const glm::vec3& delta);

		void setHorizontalAngle(float a);
		void updateHorizontalAngle(float deltaA);
		void setVerticalAngle(float a);
		void updateVerticalAngle(float deltaA);

		const glm::mat4& getProjectionMatrix() const;
		const glm::mat4& getViewMatrix() const;
		const glm::vec3& getFront() const;
		const glm::vec3& getRight() const;

		glm::mat4 transform (const glm::mat4& modelMatrix) const;
};
