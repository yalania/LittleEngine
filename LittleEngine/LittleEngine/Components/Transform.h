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
	glm::mat4 CalculateTransformMatrix();

};

#endif // !_TRANSFORM_COMPONENT_

