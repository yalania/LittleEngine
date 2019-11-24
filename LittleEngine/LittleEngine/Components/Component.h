#ifndef _COMPONENT_
#define _COMPONENT_
#include "../Globals.h"
#include <memory>


enum class ComponentType {
	TRANSFORM,
	MESH
};

class GameObject;
class Component {

public:
	Component(GameObject * owner,ComponentType componentType) : owner(owner), type(componentType) {}
	virtual ~Component() = default;

	virtual void Enable()
	{
		active = true;
	}

	virtual void Update() {};

	virtual void Disable()
	{
		active = false;
	}

	bool active = true;
	ComponentType type;

	void SetOwner(GameObject * owner);
	GameObject * const GetOwner() const;
private:
	GameObject * owner;
};
#endif // !_COMPONENT_

