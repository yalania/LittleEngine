#ifndef _SHADERS_PROGRAM_
#define _SHADERS_PROGRAM_
#include <string>
#include <GL/glew.h>
#include "Module.h"
class ModuleProgram : public Module {

public:
	ModuleProgram() = default;
	~ModuleProgram();
	bool Init() override;
	bool CleanUp() override;

	GLuint defaultProgram;
	GLuint LoadShaderProgram(const char *vertex_path, const char *fragment_path) const;
	unsigned int uniformsBuffer;
private:

	const std::string ReadFile(const std::string & shaderFilePath) const;
	void CompileShader(const GLuint & shader, const char * shaderFile) const;
	void SetUpUniformSBuffer();
};
#endif // _SHADERS_PROGRAM_

