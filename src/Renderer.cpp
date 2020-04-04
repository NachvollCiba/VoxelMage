#include "Renderer.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


Renderer::Renderer(const Camera& camera, const ShaderManager& shaderManager) :
	_camera(camera),
	_shaderManager(shaderManager)
{
	this->_shaderProgramID
	 = shaderManager.loadShaders("TestVertexShader.vs", "TestFragmentShader.fs");

	glGenBuffers(2, this->_buffers);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}


Renderer::~Renderer() {
	glDeleteBuffers(2, this->_buffers);
	glDeleteProgram(this->_shaderProgramID);
}


void Renderer::renderCube(const glm::vec3& pos, float scale, const glm::vec3& color) {

	// compute model and mvp matrices
	glm::mat4 model = glm::translate(glm::mat4(1.0), pos);
	if (scale != 1.0f) {
		model = model * glm::scale(glm::vec3(scale));
	}
	this->_cubes.push_back(model);

	static const GLfloat bufferData[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	GLfloat colorData[12*3*3];
	for (int i=0; i < 12*3; i++) {
		colorData[3*i] = color[0];
		colorData[3*i+1] = color[1];
		colorData[3*i+2] = color[2];
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->_buffers[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->_buffers[COLOR_BUFFER]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
}

void Renderer::update() {
	for (glm::mat4& model : this->_cubes) {
		glm::mat4 mvp = this->_camera.transform(model);

		glUseProgram(this->_shaderProgramID);
		GLuint matrixID = glGetUniformLocation(this->_shaderProgramID, "MVP");
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->_buffers[VERTEX_BUFFER]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, this->_buffers[COLOR_BUFFER]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

		glDrawArrays(GL_TRIANGLES, 0, 12*3);
		glDisableVertexAttribArray(0);
	}
}
