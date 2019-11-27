#include "GameObject.h"
#include "LittleEngine.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
GameObject::GameObject(const char * name, GameObject* parent) : name(std::string(name)), transform(this), parent(parent){
}
GameObject::GameObject(std::string name, GameObject* parent) : name(name), transform(this), parent(parent) {
}

GameObject::~GameObject() {
	for (auto & child : children)
	{
		child->Delete();
	}
	children.clear();

	for (auto & componet : components)
	{
		componet->Delete();
	}
	components.clear();
	parent->RemoveChild(this);
}

void GameObject::Update(){
	transform.Update();
}

void GameObject::SetParent(GameObject * parent) {
	//New Parent is not is child
	GameObject * grandFather = parent->parent;
	while (grandFather != nullptr) {
		if (grandFather == this) {
			return;
		}
		grandFather = grandFather->parent;
	}
	this->parent->RemoveChild(this);
	this->parent = parent;
	parent->children.push_back(this);
}
void GameObject::RemoveChild(GameObject * gameObject) {
	if (!children.empty()) {
		auto it = std::remove_if(children.begin(), children.end(), [gameObject](GameObject* child)
		{ 
			return child == gameObject;  
		});
		children.erase(it);
	}
}

void GameObject::AddChild(GameObject * gameObject) {
	gameObject->SetParent(this);
}

void GameObject::Delete() {
	Engine->moduleSceneManager->RemoveGameObject(this);
}

std::vector<Component *> GameObject::GetComponents(ComponentType type) {
	std::vector<Component *> result;
	for (auto & component : components) {
		result.push_back(component);
	}
	return result;
}