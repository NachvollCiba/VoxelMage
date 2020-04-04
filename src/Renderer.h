#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "ShaderManager.h"

class Renderer {

	private:
		static const int VERTEX_BUFFER = 0;
		static const int COLOR_BUFFER = 1;

		const Camera& _camera;
		const ShaderManager& _shaderManager;

		GLuint _shaderProgramID;
		GLuint _buffers[2];

		std::vector<glm::mat4> _cubes;

	public:
		Renderer(const Camera& camera, const ShaderManager& shaderManager);
		~Renderer();

		void renderCube(const glm::vec3& position, float scale=1.0f, const glm::vec3& color=glm::vec3(1.0f, 0.0f, 0.0f));
		void update();

};
