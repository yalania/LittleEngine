#include "Transform.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


Transform::Transform(unsigned int shaderProgram) {
	modelShaderOutput = glGetUniformLocation(shaderProgram,"model");
	UpdateModel();
}
void Transform::UpdateModel() const{
	glUniformMatrix4fv(modelShaderOutput, 1, GL_FALSE, glm::value_ptr(model));
}