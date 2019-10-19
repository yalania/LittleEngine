#include "ShaderProgram.h"
#include "Globals.h"
#include <fstream>
#include <vector>


const char * ShaderProgram::readFile(const std::string & shaderFilePath){
	std::ifstream file(shaderFilePath, std::ios::in);

	if (!file.is_open()) {
		LOG("Shader couldn't be opened! File path: %s\n", shaderFilePath);
		return false;
	}

	std::string shader((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	file.close();
	return shader.c_str();
	
}

void ShaderProgram::compileShader(const GLuint & shader, const char * shaderFile){

	GLint result = GL_FALSE;
	int logLength;

	glShaderSource(shader, 1, &shaderFile, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);

	glGetShaderInfoLog(shader, logLength, NULL, &vertShaderError[0]);
	LOG("Shader coudn't be compiled : %s\n", &vertShaderError[0]);
}


GLuint ShaderProgram::loadShaderProgram(const char *vertex_path, const char *fragment_path){

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	GLint result = GL_FALSE;
	int logLength;

	GLuint program = glCreateProgram();

	const char * vertexShaderFile = readFile(vertex_path);
	const char * farmentShaderFile = readFile(fragment_path);

	compileShader(vertexShader, vertexShaderFile);
	compileShader(fragmentShader, farmentShaderFile);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> programError((logLength > 1) ? logLength : 1);
	glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
	LOG("Problems linking  : %s\n", &programError[0]);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;


}