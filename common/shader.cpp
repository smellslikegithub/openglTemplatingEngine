#include<GL/glew.h> // make sure this is the first include
#include <GLFW/glfw3.h>
#include<iostream>
#include<string>
#include <fstream>
#include "shader.hpp"




bool static _isThisCharArrayNullOrEmpty(const char* _this)
{
	if (_this && !_this[0]) {
		std::cerr << "The object is either empty of NULL" << std::endl;
		throw std::runtime_error("The object is either empty of NULL");
	}
	return false;
}

std::string static _getContentsFromFile(const char* filePath){
	std::string accumulatedContent;
	std::ifstream file(filePath, std::ios::in);

	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return "";
	}

	std::string line;
	while (std::getline(file, line)) {
		// Process the line
		std::cout << line << std::endl; 
		accumulatedContent += "\n" + line;
	}

	file.close();

	return accumulatedContent;
}


GLuint LoadShadersFromFile(const char* vertexShaderFilePath, const char* fragmentShaderFilePath) {
	if (!_isThisCharArrayNullOrEmpty(vertexShaderFilePath) && !_isThisCharArrayNullOrEmpty(fragmentShaderFilePath)) {
		
		// Read and load the content of the vertex shader in ram
		std::string vertexShaderSource = _getContentsFromFile(vertexShaderFilePath);
		std::string fragmentShaderSource = _getContentsFromFile(fragmentShaderFilePath);

		if (vertexShaderSource == "" || fragmentShaderSource == "") {
			std::cerr << "Vertex/Frament shader content is empty!"<<std::endl << "Frgament Shader = " << fragmentShaderSource << std::endl << "Vertex Shader = " << vertexShaderSource << std::endl;
			return 0;
		}

		int success;
		char infoLog[512];

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* vertexShaderSourceChar = vertexShaderSource.c_str();
		const GLchar* fragmentShaderSourceChar = fragmentShaderSource.c_str();

		glShaderSource(vertexShader, 1, &vertexShaderSourceChar, NULL);
		glCompileShader(vertexShader);

		// Check for compilation errors
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Fragment Shader
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSourceChar, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);


		if (!success) {
			glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
				infoLog << std::endl;
		}

		// Shader Program
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();

		// STEP 6 Attach previously compiled shaders to the Shader Program.
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// We no longer need the shaders anymore since it is loaded into the program.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);



		return shaderProgram;
		

	} 

	return 0;

}



GLuint LoadShaders(const char* vertexShaderCode, const char* fragmentShaderCode) {
	int success;
	char infoLog[512];

	
	if (!_isThisCharArrayNullOrEmpty(vertexShaderCode) && !_isThisCharArrayNullOrEmpty(fragmentShaderCode)) {
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
		glCompileShader(vertexShader);

		// Check for compilation errors
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Fragment Shader
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);


		if (!success) {
			glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
				infoLog << std::endl;
		}

		// Shader Program
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();

		// STEP 6 Attach previously compiled shaders to the Shader Program.
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// We no longer need the shaders anymore since it is loaded into the program.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);



		return shaderProgram;
	}
}