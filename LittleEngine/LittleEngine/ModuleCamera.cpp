#include "ModuleCamera.h"
#include "LittleEngine.h"
#include <GL/glew.h>

bool ModuleCamera::Init() {
	view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	return true;
}

update_status ModuleCamera::PreUpdate() {
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	GLuint viewOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"view");
	glUniformMatrix4fv(viewOutput, 1, GL_FALSE, glm::value_ptr(view));
	return UPDATE_CONTINUE;
}

void ModuleCamera::Rotate(const glm::vec2 & mouseOffset) {

	yaw += mouseOffset.x;
	pitch += mouseOffset.y;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);

}

void ModuleCamera::Translate(glm::vec4 direction) {

	if (direction.x != 0)
		cameraPos -= cameraSpeed * cameraUp;
	if (direction.y != 0)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (direction.z != 0)
		cameraPos += cameraSpeed * cameraUp;
	if (direction.w != 0)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}