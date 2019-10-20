#ifndef _SHADERS_PROGRAM_
#define _SHADERS_PROGRAM_
#include <string>
#include "GL/glew.h"

class ShaderProgram {

public:

	static GLuint loadShaderProgram(const char *vertex_path, const char *fragment_path);

private:

	static const std::string readFile(const std::string & shaderFilePath);
	static void compileShader(const GLuint & shader, const char * shaderFile);
};
#endif // _SHADERS_PROGRAM_

