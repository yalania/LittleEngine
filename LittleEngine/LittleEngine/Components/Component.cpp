#include "Component.h"
#include "../GameObject.h"

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
