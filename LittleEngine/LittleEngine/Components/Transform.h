#ifndef _TRANSFORM_COMPONENT_
#define _TRANSFORM_COMPONENT_
#include "Component.h"
#include "glm.hpp"
class Transform : public Component {
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

};

#endif // !_TRANSFORM_COMPONENT_

