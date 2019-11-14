#include "Transform.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "../LittleEngine.h"

Transform::Transform(unsigned int shaderProgram) {
	modelShaderOutput = glGetUniformLocation(shaderProgram,"model");
	UpdateModel();
}
void Transform::UpdateModel(){
	/*double movementInX = sin(Engine->moduleTimeController->gameTimeClock.Read()/1000);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(movementInX,0.0f,0.0f));*/
	glUniformMatrix4fv(modelShaderOutput, 1, GL_FALSE, glm::value_ptr(model));
}