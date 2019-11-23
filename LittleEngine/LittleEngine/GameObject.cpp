#include "GameObject.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


GameObject::GameObject(const char * name) : name(std::string(name)){
}


void GameObject::Update(){
	glUseProgram(shaderProgram);
	if (!gameIsPaused) {
		transform.Update();
	}
	//update_status result = model->Update();
	glUseProgram(0);
}