#include "GameObject.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

GameObject::GameObject(const char * name, GameObject* parent) : name(std::string(name)), transform(this), parent(parent){
}
GameObject::GameObject(std::string name, GameObject* parent) : name(name), transform(this), parent(parent) {
}

void GameObject::Update(){
	transform.Update();
}

void GameObject::SetParent(GameObject * parent) {
	this->parent->RemoveChildren(this);
	this->parent = parent;
	parent->children.push_back(this);
}
void GameObject::RemoveChildren(GameObject * gameObject) {
	if (!children.empty()) {
		auto it = std::remove_if(children.begin(), children.end(), [gameObject](GameObject* child)
		{ 
			return child == gameObject;  
		});
		children.erase(it);
	}
}

std::vector<Component *> GameObject::GetComponents(ComponentType type) {
	std::vector<Component *> result;
	for (auto & component : components) {
		result.push_back(component);
	}
	return result;
}