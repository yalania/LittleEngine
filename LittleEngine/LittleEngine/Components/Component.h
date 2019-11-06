#ifndef _COMPONENT_
#define _COMPONENT_
#include "../Globals.h"
class Component {

	Component() = default;
	virtual ~Component() = default;

	virtual bool Init()
	{
		return true;
	}

	virtual update_status Update() {
		return UPDATE_CONTINUE;
	};

	virtual bool CleanUp()
	{
		return true;
	}
};
#endif // !_COMPONENT_

