#include "Transform.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "../LittleEngine.h"

Transform::Transform(GameObject * owner) : Component(owner, ComponentType::TRANSFORM) {
	CalculateTransformMatrix();
}
void Transform::Update(){
	CalculateTransformMatrix();
	UpdateModelInUniformBuffer();
}

glm::mat4 & Transform::CalculateTransformMatrix()  {
	glm::mat4 globalMatrix = glm::mat4(1.0f);
	if (owner->parent != nullptr) {
		globalMatrix = owner->parent->transform.model;
	}
	model = glm::mat4(1.0f);
	rotation = glm::normalize(rotation);
	model = glm::mat4_cast(rotation);
	model *= glm::vec4(scale, 1.0f);
	model[3][0] = position.x;
	model[3][1] = position.y;
	model[3][2] = position.z;
	model = globalMatrix * model;
	return model;
}

void Transform::TranslateLocal(const glm::vec3 & translation) {
		position += translation.x * glm::vec3(model[0]);
		position += translation.y * glm::vec3(model[1]);
		position += translation.z * glm::vec3(model[2]);
}

void Transform::RotateLocal(const glm::quat & rotation){}
void Transform::RotateLocal(const glm::vec3 & rotationEuler){}
void Transform::ScaleLocal(const glm::vec3 & scale){}

void Transform::SetRotationFromEuler(const glm::vec3 & eulerRotation) {
	rotation = glm::quat(eulerRotation);
}

glm::vec3 Transform::GetEulerRotation() const {
	return glm::eulerAngles(rotation);
}

glm::vec3 Transform::GetRightAxis() const {
	return model[0];
}
glm::vec3 Transform::GetUptAxis() const{
	return model[1];
}
glm::vec3 Transform::GetFrontAxis() const{
	return model[2];
}

void Transform::UpdateModelInUniformBuffer() {
	glBindBuffer(GL_UNIFORM_BUFFER, Engine->moduleShaderProgram->uniformsBuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(model));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}