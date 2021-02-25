#include "Log.h"
#include <stdio.h>

static ImGuiTextBuffer logData;

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	logData.appendfv(tmp_string,ap);
	logData.append("\n");
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);

	//OutputDebugString(tmp_string2);
}


void __stdcall OurOpenGLErrorFunction(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam)
{

	char tmp_string[4096];
	static va_list ap;
	//va_start(ap, message);
	//vsprintf_s(tmp_string, 4096, message, ap);
	//logData.appendfv(tmp_string, ap);
	//logData.append("\n");
	//va_end(ap);


	//OutputDebugString(tmp_string);
}

const ImVector<char> * getLogData() {
	return &logData.Buf;
}

bool clearLogData() {
	logData.clear();
	return logData.empty();
}

void AssimpLog::write(const char* message) {
	static char tmp_string[4096];
	static va_list ap;
	//va_start(ap, message);
	//vsprintf_s(tmp_string, 4096, message, ap);
	//logData.appendfv(tmp_string, ap);
	//va_end(ap);
}