#include "ModuleCamera.h"
#include "LittleEngine.h"
#include <GL/glew.h>

bool ModuleCamera::Init() {
	view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
	return true;
}

update_status ModuleCamera::PreUpdate() {
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	GLuint viewOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"view");
	GLuint projOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"proj");
	glUniformMatrix4fv(viewOutput, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projOutput, 1, GL_FALSE, glm::value_ptr(projection));
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

void ModuleCamera::Translate(const glm::vec4 & direction) {

	if (direction.x != 0)
		cameraPos -= cameraSpeed * cameraUp;
	if (direction.y != 0)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (direction.z != 0)
		cameraPos += cameraSpeed * cameraUp;
	if (direction.w != 0)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void ModuleCamera::Zoom(bool zoomIn) {

	if (zoomIn) {
		cameraPos.z -= 0.1f;
	}
	else {
		cameraPos.z += 0.1f;
	}
}

void ModuleCamera::ChangeProjection() {

	if (perspectiveEnable) {
		projection = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		perspectiveEnable = false;
	}
	else {
		perspectiveEnable = false;
		projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
	}
	

}