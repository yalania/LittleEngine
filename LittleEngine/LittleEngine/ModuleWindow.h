#ifndef _MODULE_WINDOW_
#define _MODULE_WINDOW_

#include "Module.h"
#include <SDL/SDL.h>
class LittleEngine;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	~ModuleWindow();

	bool Init() override;
	bool CleanUp() override;

private:
	void InitOpenGLAttributes();

public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;
};

#endif // !_MODULE_WINDOW_

