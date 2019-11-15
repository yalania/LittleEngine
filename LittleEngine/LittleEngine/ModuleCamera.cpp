#include "ModuleCamera.h"
#include "LittleEngine.h"
#include <GL/glew.h>

bool ModuleCamera::Init() {
	LOG("Init Camera System");

	// note that we're translating the scene in the reverse direction of where we want to move
	UpdateMatricesInShaderPograms();
	LoadProjection();
	return true;
}

update_status ModuleCamera::PreUpdate() {
	UpdateMatricesInShaderPograms();
	return UPDATE_CONTINUE;
}

void ModuleCamera::MoveCameraWithMousePosition(const glm::vec2 & mouseOffset) {
	
	glm::mat4 model = transform.CalculateTransformMatrix();
	glm::quat rotX = glm::angleAxis(mouseOffset.y * cameraSpeed, glm::vec3(model[0]));
	glm::quat rotY = glm::angleAxis(mouseOffset.x * cameraSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
	transform.rotation = rotY * rotX* transform.rotation;
}

void ModuleCamera::Translate(const glm::vec3 & direction) {

	glm::mat4 model = transform.CalculateTransformMatrix();

	if (direction.y > 0) {
		transform.position -= cameraSpeed * glm::vec3(model[1]);
	}
	if (direction.y < 0) {
		transform.position += cameraSpeed * glm::vec3(model[1]);
	}
	if (direction.x > 0) {
		transform.position -= cameraSpeed * glm::vec3(model[0]);
	}
	if (direction.x < 0) {
		transform.position += cameraSpeed * glm::vec3(model[0]);
	}
	if (direction.z > 0) {
		transform.position -= cameraSpeed * glm::vec3(model[2]);
	}
	if (direction.z < 0) {
		transform.position += cameraSpeed * glm::vec3(model[2]);
	}

}

void ModuleCamera::Zoom(bool zoomIn) {

	glm::mat4 model = transform.CalculateTransformMatrix();
	if (zoomIn) {
		/*orthoUnits -= 0.05f;
		--frustumFov;
		orthoUnits = orthoUnits <= 0 ? 0.0f : orthoUnits;
		frustumFov = frustumFov <= 0 ? 0.0f : frustumFov;*/
		transform.position += cameraSpeed * glm::vec3(model[2]);
	}
	else {
		/*orthoUnits += 0.05;
		++frustumFov;
		frustumFov = frustumFov > 179.9 ? 179.9f : frustumFov;*/
		transform.position -= cameraSpeed * glm::vec3(model[2]);
	}
}

void ModuleCamera::EnablePerspective() {
		perspectiveEnable = true;
		LoadProjection();
}

void ModuleCamera::EnableOrthographic() {
		perspectiveEnable = false;
		LoadProjection();
}

void ModuleCamera::LoadProjection() {
	aspect = static_cast<float>(Engine->moduleWindow->width) / static_cast<float>(Engine->moduleWindow->height);
	if (perspectiveEnable) {
		projection = glm::perspective(glm::radians(frustumFov), aspect, nearPlane, farPlane);
	}
	else {
		projection = glm::ortho(-orthoUnits * aspect, orthoUnits * aspect, -orthoUnits, orthoUnits, nearPlane, farPlane);
	}
}

void ModuleCamera::UpdateMatricesInShaderPograms(){

	view = glm::inverse(transform.CalculateTransformMatrix());
	glBindBuffer(GL_UNIFORM_BUFFER, Engine->moduleShaderProgram->uniformsBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, Engine->moduleShaderProgram->uniformsBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void ModuleCamera::FocusOnEntity(const Entity & entity) {
	transform.position = entity.entityModel->sphereCenter;
	float distance = entity.entityModel->sphereRadius / tan(glm::radians(frustumFov / 2));
	transform.position.z += distance;;
	view = glm::lookAt(transform.position, entity.entityModel->sphereCenter, glm::vec3(0.0f,1.0f, 0.0f));
	transform.rotation = glm::quat(glm::inverse(view));

}
