#pragma once

#include <GLFW/glfw3.h>
#include <string>

class ShaderManager {

	private:
		std::string _shaderPath;

	public:
		ShaderManager(const std::string shaderPath);
		
		GLuint loadShaders(std::string vertexShader, std::string fragmentShader) const;
};
