#ifndef _TRANSFORM_COMPONENT_
#define _TRANSFORM_COMPONENT_
#include "Component.h"
#include <glm/glm.hpp>
class Transform : public Component {

public:
	Transform(unsigned int shaderProgram);
	void UpdateModel() const;
private:
	glm::vec3 position = glm::vec3(1.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 rotation = glm::vec3(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	unsigned int modelShaderOutput;

};

#endif // !_TRANSFORM_COMPONENT_

