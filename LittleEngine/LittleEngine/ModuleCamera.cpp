#include "ModuleCamera.h"
#include "LittleEngine.h"
#include <GL/glew.h>

bool ModuleCamera::Init() {
	LOG("Init Camera System");
	UpdateMatricesInShaderPograms();
	UpdateProjection();
	return true;
}

update_status ModuleCamera::PreUpdate() {
	UpdateMatricesInShaderPograms();
	return UPDATE_CONTINUE;
}

void ModuleCamera::MoveCameraWithMousePosition(const glm::vec2 & mouseOffset) {
	glm::quat rotX = glm::angleAxis(mouseOffset.y * cameraSpeed, glm::vec3(transform->GetRightAxis()));
	glm::quat rotY = glm::angleAxis(mouseOffset.x * cameraSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
	transform->rotation = rotY * rotX* transform->rotation;
}

void ModuleCamera::Translate(const glm::vec3 & direction) {
	glm::vec3 translationDirection = glm::vec3(direction.x, -direction.y, direction.z);
	transform->TranslateLocal(translationDirection * cameraSpeed);
}

void ModuleCamera::Zoom(bool zoomIn) {

	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);
	if (zoomIn) {
		orthoUnits -= 0.05f;
		orthoUnits = orthoUnits <= 0 ? 0.0f : orthoUnits;
		--frustumFov;
		frustumFov = frustumFov <= 0 ? 0.0f : frustumFov;
		direction *= cameraSpeed;
	}
	else {
		/*
		orthoUnits += 0.05;
		++frustumFov;
		frustumFov = frustumFov > 179.9 ? 179.9f : frustumFov;*/
		direction *= -cameraSpeed;
	}
	transform->TranslateLocal(direction);
}

void ModuleCamera::SetAspectRatio(float newAspectRatio) {
	this->aspect = newAspectRatio;
	UpdateProjection();
}

void ModuleCamera::UpdateProjection() {
	if (perspectiveEnable) {
		projection = glm::perspective(glm::radians(frustumFov), aspect, nearPlane, farPlane);
	}
	else {
		projection = glm::ortho(-orthoUnits * aspect, orthoUnits * aspect, -orthoUnits, orthoUnits, nearPlane, farPlane);
	}
}

void ModuleCamera::UpdateMatricesInShaderPograms(){

	view = glm::inverse(transform->CalculateTransformMatrix());
	glBindBuffer(GL_UNIFORM_BUFFER, Engine->moduleShaderProgram->uniformsBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, Engine->moduleShaderProgram->uniformsBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void ModuleCamera::FocusOnEntity(const Entity & entity) {
	transform->position = entity.entityModel->sphereCenter;
	float distance = entity.entityModel->sphereRadius / tan(glm::radians(frustumFov / 2));
	transform->position.z += distance;
	view = glm::lookAt(transform->position, entity.entityModel->sphereCenter, glm::vec3(0.0f,1.0f, 0.0f));
	transform->rotation = glm::quat(glm::inverse(view));
	orthoUnits = entity.entityModel->sphereRadius;
	UpdateProjection();
}

void ModuleCamera::OrbitAroundEntity(const Entity & entity, const glm::vec2 & mouseOffset) {

	glm::vec3 vector = transform->position - entity.entityModel->sphereCenter;
	glm::quat rotX = glm::angleAxis(mouseOffset.y * cameraSpeed, glm::vec3(transform->GetRightAxis()));
	glm::quat rotY = glm::angleAxis(mouseOffset.x * cameraSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
	vector = rotX * vector;

	float newAngle = std::abs(glm::dot(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(vector)));
	float oldAngle = std::abs(glm::dot(glm::vec3(0.0f, 1.0f, 0.0f), transform->GetFrontAxis()));

	if (newAngle < 0.99f || oldAngle > newAngle) {
		vector = rotY * vector;
		transform->position = entity.entityModel->sphereCenter + vector;
		view = glm::lookAt(transform->position, entity.entityModel->sphereCenter, glm::vec3(0.0f, 1.0f, 0.0f));
		transform->rotation = glm::quat(glm::inverse(view));
	}
	
}
