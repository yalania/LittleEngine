#ifndef _MODULE_
#define _MODULE_

#include "Globals.h"
#include "Log.h"

class Module
{
public:

	Module() = default;

	virtual ~Module() = default;

	virtual bool Init()
	{
		return true;
	}

	virtual update_status PreUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}
};

#endif // _MODULE_
