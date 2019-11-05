#include "ModuleCamera.h"
#include "LittleEngine.h"
#include <GL/glew.h>

bool ModuleCamera::Init() {
	LOG("Init Camera System");

	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
	LoadProjection();
	return true;
}

update_status ModuleCamera::PreUpdate() {
	view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
	GLuint viewOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"view");
	GLuint projOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"proj");
	glUniformMatrix4fv(viewOutput, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projOutput, 1, GL_FALSE, glm::value_ptr(projection));
	return UPDATE_CONTINUE;
}

void ModuleCamera::MoveCameraWithMousePosition(const glm::vec2 & mouseOffset) {

	yaw += mouseOffset.x;
	pitch += mouseOffset.y;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);

	cameraRight = glm::normalize(glm::cross(cameraUp, cameraFront));

}

void ModuleCamera::Translate(const glm::vec2 & direction) {

	if (direction.y > 0) {
		cameraPosition -= cameraSpeed * cameraUp;
	}
	if (direction.y < 0) {
		cameraPosition += cameraSpeed * cameraUp;
	}
	if (direction.x > 0) {
		cameraPosition +=  cameraSpeed * cameraRight;
	}
	if (direction.x < 0) {
		cameraPosition -= cameraSpeed * cameraRight;
	}
}

void ModuleCamera::Zoom(bool zoomIn) {

	if (zoomIn) {
		orthoUnits -= 0.05f;
		orthoUnits = orthoUnits <= 0 ? 0.0f : orthoUnits;
		--frustumFov;
	}
	else {
		orthoUnits += 0.05;
		++frustumFov;
	}
	LoadProjection();

}

void ModuleCamera::EnablePerspective() {

	if (!perspectiveEnable) {
		projection = glm::perspective(glm::radians(frustumFov), aspect, 0.1f, 100.0f);
		perspectiveEnable = true;
	}
}

void ModuleCamera::EnableOrthographic() {

	if (perspectiveEnable) {
		float orthoUnitsAbs = abs(orthoUnits);
		projection = glm::ortho(-orthoUnits * aspect, orthoUnits * aspect, -orthoUnits, orthoUnits, 0.1f, 100.0f);
		perspectiveEnable = false;
	}

}

void ModuleCamera::LoadProjection() {
	if (perspectiveEnable) {
		projection = glm::perspective(glm::radians(frustumFov), aspect, 0.1f, 100.0f);
	}
	else {
		projection = glm::ortho(-orthoUnits * aspect, orthoUnits * aspect, -orthoUnits, orthoUnits, 0.1f, 100.0f);
	}
}