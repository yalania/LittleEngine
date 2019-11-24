#include "GameObject.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


GameObject::GameObject(const char * name) : name(std::string(name)), transform(this){
}
GameObject::GameObject(std::string name) : name(name), transform(this) {
}

void GameObject::Update(){
}

std::vector<Component *> GameObject::GetComponents(ComponentType type) {
	std::vector<Component *> result;
	for (auto & component : components) {
		result.push_back(component);
	}
	return result;
}