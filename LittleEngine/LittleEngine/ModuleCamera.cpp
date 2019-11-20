#include "ModuleCamera.h"
#include "LittleEngine.h"
#include <GL/glew.h>

bool ModuleCamera::Init() {
	LOG("Init Camera System");
	UpdateProjection();
	return true;
}

update_status ModuleCamera::PreUpdate() {
	UpdateMatricesInShaderPograms();
	return UPDATE_CONTINUE;
}

void ModuleCamera::MoveCameraWithMousePosition(const glm::vec2 & mouseOffset) {
	glm::quat rotX = glm::angleAxis(mouseOffset.y * cameraSpeedMouse, glm::vec3(transform->GetRightAxis()));
	glm::quat rotY = glm::angleAxis(mouseOffset.x * cameraSpeedMouse, glm::vec3(0.0f, 1.0f, 0.0f));
	transform->rotation = rotY * rotX* transform->rotation;
}

void ModuleCamera::Translate(const glm::vec3 & direction) {
	glm::vec3 translationDirection = glm::vec3(direction.x, -direction.y, direction.z);
	transform->TranslateLocal(translationDirection * cameraSpeedKeys);
}

void ModuleCamera::Zoom(bool zoomIn) {

	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);
	if (zoomIn) {
		/*orthoUnits -= 0.05f;
		orthoUnits = orthoUnits <= 0 ? 0.0f : orthoUnits;
		--frustumFov;
		frustumFov = frustumFov <= 0 ? 0.0f : frustumFov;*/
		direction *= -cameraSpeedKeys;
	}
	else {
		/*
		orthoUnits += 0.05;
		++frustumFov;
		frustumFov = frustumFov > 179.9 ? 179.9f : frustumFov;*/
		direction *= cameraSpeedKeys;
	}
	transform->TranslateLocal(direction);
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

	float amountInDifferentDirection = glm::dot(glm::normalize(vector),entity.entityTransform->GetFrontAxis());
	//If -1 looking they are looking in opposite directions
	if (amountInDifferentDirection < 0.0f) {
		view = glm::lookAt(transform->position, entity.entityModel->sphereCenter, glm::vec3(0.0f, 1.0f, 0.0f));
		transform->rotation = glm::quat(glm::inverse(view));
	}
	glm::quat rotX = glm::angleAxis(mouseOffset.y * cameraSpeedMouse, glm::vec3(transform->GetRightAxis()));
	glm::quat rotY = glm::angleAxis(mouseOffset.x * cameraSpeedMouse, glm::vec3(0.0f, 1.0f, 0.0f));
	vector = rotX * vector;
	vector = rotY * vector;
	transform->position = entity.entityModel->sphereCenter + vector;
	MoveCameraWithMousePosition(mouseOffset);
}

//Setters
void ModuleCamera::SetAspectRatio(float newAspectRatio) {
	this->aspect = newAspectRatio;
	UpdateProjection();
}

void ModuleCamera::SetFarPlane(float newFarPlane) {
	this->farPlane = newFarPlane;
	UpdateProjection();
}
void ModuleCamera::SetNearPlane(float newNearPlane) {
	this->nearPlane = newNearPlane;
	UpdateProjection();
}
void ModuleCamera::SetPerspectiveEnable(bool perspective) {
	this->perspectiveEnable = perspective;
	UpdateProjection();
}

void ModuleCamera::SetHorizontalFov(float horizontalFov) {
	this->frustumFov = horizontalFov;
	UpdateProjection();
}