#include "Entity.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "LittleEngine.h"
Entity::Entity(std::vector<Mesh> entityMeshes, unsigned int  shaderProgram) : entityMeshes(entityMeshes), shaderProgram(shaderProgram){
	entityTransform = std::make_unique<Transform>(shaderProgram);
}


update_status Entity::Update(){
	glUseProgram(shaderProgram);
	entityTransform->UpdateModel();
	update_status result = UPDATE_CONTINUE;
	for (auto &mesh : entityMeshes) {
		mesh.Update();
	}
	glUseProgram(0);
	return result;

}