#ifndef _MODULE_
#define _MODULE_

#include <Globals.h>
#include "Log.h"
#include <vector>
#include <memory>
#include <string>
class Module
{
public:

	Module() = default;

	virtual ~Module() = default;

	virtual bool Init()
	{
		return true;
	}

	virtual UpdateStatus PreUpdate()
	{
		return UpdateStatus::UPDATE_CONTINUE;
	}

	virtual UpdateStatus Update()
	{
		return UpdateStatus::UPDATE_CONTINUE;
	}

	virtual UpdateStatus PostUpdate()
	{
		return UpdateStatus::UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}
};

#endif // _MODULE_
