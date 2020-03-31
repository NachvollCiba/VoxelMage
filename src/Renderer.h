#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Renderer {

	private:
		GLuint vertexArrayID;

	public:
		Renderer();

		void drawTriangle(GLfloat coordinates[]);
};
