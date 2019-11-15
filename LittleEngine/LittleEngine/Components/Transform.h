#ifndef _TRANSFORM_COMPONENT_
#define _TRANSFORM_COMPONENT_
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
class Transform : public Component {

public:
	Transform();
	void UpdateModel();
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::quat rotation = glm::quat(1.0,0.f,0.f,0.f);
	glm::vec3 GetRightAxis();
	glm::vec3 GetUptAxis();
	glm::vec3 GetFrontAxis();
	void TranslateLocal(glm::vec3 translation);
	glm::mat4 CalculateTransformMatrix();

private:
	glm::mat4 model;

};

#endif // !_TRANSFORM_COMPONENT_

