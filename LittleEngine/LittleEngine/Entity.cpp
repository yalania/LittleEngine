#include "Entity.h"
#include <GL/glew.h>

Entity::Entity(Mesh mesh, unsigned int  shaderProgram) : entityMesh(std::make_unique<Mesh>(mesh)), shaderProgram(shaderProgram){
	entityTransform = std::make_unique<Transform>(shaderProgram);
}


update_status Entity::Update(){
	glUseProgram(shaderProgram);
	update_status result = UPDATE_CONTINUE;
	//result = entityMesh->Update();
	return result;

}