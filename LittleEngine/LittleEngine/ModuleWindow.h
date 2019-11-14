#ifndef _MODULE_WINDOW_
#define _MODULE_WINDOW_

#include "Module.h"
#include <SDL/SDL.h>


class ModuleWindow : public Module
{
public:

	ModuleWindow() = default;
	~ModuleWindow();

	bool Init() override;
	bool CleanUp() override;

	void WindowResized(unsigned width, unsigned height);

private:
	void InitOpenGLAttributes();

public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;

	int width = SCREEN_WIDTH;
	int height = SCREEN_HEIGHT;
};

#endif // !_MODULE_WINDOW_

