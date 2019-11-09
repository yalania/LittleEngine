#include "Entity.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "LittleEngine.h"
Entity::Entity(std::vector<Mesh> entityMeshes, unsigned int  shaderProgram) : entityMeshes(entityMeshes), shaderProgram(shaderProgram){
	//entityTransform = std::make_unique<Transform>(shaderProgram);
}


update_status Entity::Update(){
	//glUseProgram(shaderProgram);
	glUseProgram(Engine->moduleShaderProgram->defaultProgram);
	glm::mat4 model = glm::mat4(1.0f);
	GLuint modelOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"model");
	glUniformMatrix4fv(modelOutput, 1, GL_FALSE, glm::value_ptr(model));
	update_status result = UPDATE_CONTINUE;
	for (auto &mesh : entityMeshes) {
		mesh.Update();
	}
	glUseProgram(0);
	return result;

}