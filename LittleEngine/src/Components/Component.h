#ifndef _COMPONENT_
#define _COMPONENT_
#include "../Globals.h"
#include <memory>
#include <string>

enum class ComponentType {
	TRANSFORM,
	MESH
};

class GameObject;
class Component {

public:
	Component(GameObject * owner,ComponentType componentType) : owner(owner), type(componentType) {}
	virtual ~Component() = default;

	Component(const Component & component);
	Component(Component && component);

	Component& operator = (const Component & component);
	Component& operator = (Component && component);

	virtual void Enable()
	{
		active = true;
	}

	virtual void Update() {};

	virtual void Disable()
	{
		active = false;
	}
	virtual void Delete() {
		delete this;
	}
	bool active = true;
	ComponentType type;

	void SetOwner(GameObject * owner);
	GameObject * const GetOwner() const;
protected:
	GameObject * owner;
};
#endif // !_COMPONENT_

