#ifndef _MODULE_INPUT_
#define _MODULE_INPUT_

#include "Module.h"
#include "Globals.h"


class ModuleInput : public Module
{
public:
	
	ModuleInput() = default;
	~ModuleInput();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	const UINT8 *keyboard = NULL;
};

#endif // !_MODULE_RENDER_