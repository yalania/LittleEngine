#include "GameObject.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

GameObject::GameObject() : model(std::make_unique<Model>()) {
}
GameObject::GameObject(Model model, unsigned int  shaderProgram) : model(std::make_unique<Model>(model)), shaderProgram(shaderProgram){
}


update_status GameObject::Update(){
	glUseProgram(shaderProgram);
	if (!gameIsPaused) {
		transform.UpdateModel();
	}
	update_status result = model->Update();
	glUseProgram(0);
	return result;

}