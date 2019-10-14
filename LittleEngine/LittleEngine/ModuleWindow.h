#ifndef _MODULE_WINDOW_
#define _MODULE_WINDOW_

#include "Module.h"
#include "SDL/SDL.h"
class LittleEngine;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;
};

#endif // !_MODULE_WINDOW_

