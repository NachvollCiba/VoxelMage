#include <glm/glm.hpp>

#define ASPECT_16_9 16.0f/9.0f
#define ASPECT_4_3 4.0f/3.0f

class Camera {

	private:
		glm::vec3 _position;
		glm::vec3 _direction;
		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;

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

		void setDirection(float x, float y, float z);
		void setDirection(const glm::vec3& newDirection);
		void updateDirection(float dX, float dY, float dZ);
		void updateDirection(const glm::vec3& delta);

		const glm::mat4& getProjectionMatrix();
		const glm::mat4& getViewMatrix();

		glm::mat4 transform(const glm::mat4& modelMatrix);
};
