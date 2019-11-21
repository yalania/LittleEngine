#include "Entity.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

Entity::Entity() : entityModel(std::make_unique<Model>()) {
}
Entity::Entity(Model entityModel, unsigned int  shaderProgram) : entityModel(std::make_unique<Model>(entityModel)), shaderProgram(shaderProgram){
}


update_status Entity::Update(){
	glUseProgram(shaderProgram);
	if (!gameIsPaused) {
		entityTransform.UpdateModel();
	}
	update_status result = entityModel->Update();
	glUseProgram(0);
	return result;

}