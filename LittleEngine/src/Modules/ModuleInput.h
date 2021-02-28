#ifndef _MODULE_INPUT_
#define _MODULE_INPUT_

#include "Module.h"
#include <Globals.h>
#include <glm/vec2.hpp>
#include <SDL/SDL.h>

class ModuleInput : public Module
{
public:
	
	ModuleInput() = default;
	~ModuleInput();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	void CameraMovementWithMouse(const SDL_Event & event);
	void CameraMovementWithKeys();
	glm::vec2 CalculateCurrentMousePosition(const SDL_MouseMotionEvent & motion);
private:
	glm::vec2 lastMousePosition = glm::vec2(0.0f);
	const UINT8 *keyboard = NULL;
	const float mouseSensitivity = 0.5f;
	bool rightMouseButtonIsDown = false;
	bool middleMouseButtonIsDown = false;
	bool leftMouseButtonIsDown = false;
	bool shiftButtonIsDown = false;
	float cameraPreviousSpeed;
};

#endif // !_MODULE_RENDER_