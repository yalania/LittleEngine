#ifndef _TRANSFORM_COMPONENT_
#define _TRANSFORM_COMPONENT_
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
class Transform : public Component {

public:
	Transform(GameObject * owner);
	void Update() override;
	glm::vec3 GetRightAxis() const;
	glm::vec3 GetUptAxis() const;
	glm::vec3 GetFrontAxis() const;

	glm::mat4 & CalculateTransformMatrix();
	void TranslateLocal(const glm::vec3 & translation);
	void RotateLocal(const glm::quat & rotation);
	void RotateLocal(const glm::vec3 & rotationEuler);
	void ScaleLocal(const glm::vec3 & scale);

	glm::vec3 GetEulerRotation() const;
	void SetRotationFromEuler(const glm::vec3 & eulerRotation);
	void UpdateModelInUniformBuffer();

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::quat rotation = glm::quat(1.0,0.f,0.f,0.f);

private:
	glm::mat4 model;

};

#endif // !_TRANSFORM_COMPONENT_

