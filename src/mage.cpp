#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "InputHandler.h"
#include "ShaderManager.h"
#include "Camera.h"


GLFWwindow* createWindow() {
	// initialize GLFW
	if (!glfwInit()) {
		throw "Failed to initialize glfw3";
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "VoxelMage", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "FATAL ERROR: could not create GLFW Window");
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	glewExperimental=true;
	if (glewInit() != GLEW_OK) {
		throw "Failed to initialize GLEW";
	}

	return window;
}

int main(int argc, char *argv[]) {
	GLFWwindow* window = createWindow();

	InputHandler input = InputHandler(*window);
	ShaderManager shaderManager = ShaderManager("assets/shaders/");

	Camera camera = Camera(45.0f);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	GLuint programID =
	 shaderManager.loadShaders("TestVertexShader.vs", "TestFragmentShader.fs");
	GLuint matrixID = glGetUniformLocation(programID, "MVP");

	camera.setPosition(4, 3, 3);
	camera.setDirection(0, 0, 0);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 mvp = camera.transform(model);

	static const GLfloat triangle[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);


	do {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programID);
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (!input.isKeyPressed(GLFW_KEY_ESCAPE) && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vertexArrayID);
	
	glfwTerminate();
	return 0;
}

