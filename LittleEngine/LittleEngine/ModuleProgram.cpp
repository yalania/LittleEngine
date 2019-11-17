#include "ModuleProgram.h"
#include "Globals.h"
#include <fstream>
#include <vector>
#include <glm/glm.hpp>


ModuleProgram::~ModuleProgram() {
	CleanUp();
}
bool ModuleProgram::Init() {
	LOG("Init Shader program");
	defaultProgram = LoadShaderProgram("vertexShader.vert", "fragmentShader.frag");
	SetUpUniformsBuffer();
	return true;
}

const std::string ModuleProgram::ReadFile(const std::string & shaderFilePath) const{
	std::ifstream file(shaderFilePath, std::ios::in);

	if (!file.is_open()) {
		LOG("Shader couldn't be opened! File path: %s\n", shaderFilePath);
		return false;
	}

	std::string shader((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	file.close();
	return shader;
	
}

void ModuleProgram::CompileShader(const GLuint & shader, const char * shaderFile) const{

	GLint success = GL_FALSE;
	int logLength;

	glShaderSource(shader, 1, &shaderFile, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
		glGetShaderInfoLog(shader, logLength, NULL, &vertShaderError[0]);
		LOG("Shader %s coudn't be compiled : %s\n", shaderFile,&vertShaderError[0]);
	}

	
}

GLuint ModuleProgram::LoadShaderProgram(const char *vertex_path, const char *fragment_path) const{

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	GLint success = GL_FALSE;
	int logLength;

	GLuint program = glCreateProgram();

	const std::string vertexShaderFile = ReadFile(vertex_path);
	const std::string farmentShaderFile = ReadFile(fragment_path);

	CompileShader(vertexShader, vertexShaderFile.c_str());
	CompileShader(fragmentShader, farmentShaderFile.c_str());

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> programError((logLength > 1) ? logLength : 1);
		glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
		LOG("Problems linking  : %s\n", &programError[0]);
	}

	glDetachShader(program,vertexShader);
	glDetachShader(program,fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

void ModuleProgram::SetUpUniformsBuffer() {
	glGenBuffers(1, &uniformsBuffer);

	glBindBuffer(GL_UNIFORM_BUFFER, uniformsBuffer);
	glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uniformsBuffer, 0, 3 * sizeof(glm::mat4));
}
bool ModuleProgram::CleanUp() {
	glDeleteProgram(defaultProgram);
	return true;
}
