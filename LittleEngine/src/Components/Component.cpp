#include "Component.h"
#include "../GameObject.h"


Component::Component(const Component & component) = default;
Component::Component(Component && component){
	*this = std::move(component);
}

Component& Component::operator = (const Component & component) = default;

Component& Component::operator = (Component && component) {
	this->owner = component.owner;
	component.owner = nullptr;
	this->type = component.type;
	return *this;
}

void Component::SetOwner(GameObject * owner) {
	if (owner != nullptr) {
		//TODO : REMOVE OLD OWNER
	}
	owner->components.push_back(this);
	this->owner = owner;

}
GameObject * const Component::GetOwner() const {
	return owner;
}
