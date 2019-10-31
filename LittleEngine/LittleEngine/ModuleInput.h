#ifndef _MODULE_INPUT_
#define _MODULE_INPUT_

#include "Module.h"
#include "Globals.h"
#include <glm/vec2.hpp>

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
	bool rightMouseButtonIsDown = false;
	glm::vec2 initialMousePosition = glm::vec2(0.0f);
};

#endif // !_MODULE_RENDER_