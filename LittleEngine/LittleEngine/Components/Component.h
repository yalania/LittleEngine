#ifndef _COMPONENT_
#define _COMPONENT_
#include "../Globals.h"


class Component {

public:
	Component() = default;
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
};
#endif // !_COMPONENT_

