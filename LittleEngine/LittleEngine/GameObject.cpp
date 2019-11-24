#include "GameObject.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

GameObject::GameObject(const char * name, std::shared_ptr<GameObject> parent) : name(std::string(name)), transform(this), parent(parent){
}
GameObject::GameObject(std::string name, std::shared_ptr<GameObject> parent) : name(name), transform(this), parent(parent) {
}

void GameObject::Update(){
}

void GameObject::SetParent(GameObject * parent) {
	this->parent->RemoveChildren(this);
	parent->children.push_back(shared_from_this());
}
void GameObject::RemoveChildren(GameObject * gameObject) {
	if (!children.empty()) {
		std::remove_if(children.begin(), children.end(), [gameObject](std::shared_ptr<GameObject> child)
		{ return child.get() == gameObject;  });
	}
}

std::vector<Component *> GameObject::GetComponents(ComponentType type) {
	std::vector<Component *> result;
	for (auto & component : components) {
		result.push_back(component);
	}
	return result;
}