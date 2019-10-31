#include "ModuleCamera.h"
#include "LittleEngine.h"
#include <GL/glew.h>

bool ModuleCamera::Init() {
	view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	return true;
}

update_status ModuleCamera::PreUpdate() {

	GLuint viewOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"view");
	glUniformMatrix4fv(viewOutput, 1, GL_FALSE, glm::value_ptr(view));
	return UPDATE_CONTINUE;
}


void ModuleCamera::Rotate(float angle, glm::vec3 direction) {
	view = glm::rotate(view, glm::radians(angle), direction);
}

void ModuleCamera::Translate(glm::vec3 translation) {
	view = glm::translate(view, translation);
}