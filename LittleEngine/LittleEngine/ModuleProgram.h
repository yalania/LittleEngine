#ifndef _SHADERS_PROGRAM_
#define _SHADERS_PROGRAM_
#include <string>
#include "GL/glew.h"
#include "Module.h"
class ModuleProgram : public Module {

public:
	bool Init();
	GLuint defaultProgram;
private:

	GLuint LoadShaderProgram(const char *vertex_path, const char *fragment_path);
	const std::string ReadFile(const std::string & shaderFilePath);
	void CompileShader(const GLuint & shader, const char * shaderFile);
};
#endif // _SHADERS_PROGRAM_

