#ifndef _LOG_
#define _LOG_
#include <GL/glew.h>
#include "imgui/imgui.h"



#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);


void __stdcall OurOpenGLErrorFunction(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam);

const ImVector<char> * getLogData();
bool clearLogData();
#endif // !_LOG_



