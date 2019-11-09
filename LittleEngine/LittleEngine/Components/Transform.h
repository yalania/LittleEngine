#ifndef _TRANSFORM_COMPONENT_
#define _TRANSFORM_COMPONENT_
#include "Component.h"
#include <glm/glm.hpp>
class Transform : public Component {
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::mat4 model = glm::mat4(1.0f);

};

#endif // !_TRANSFORM_COMPONENT_

