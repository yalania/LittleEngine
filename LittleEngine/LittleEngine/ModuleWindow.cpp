#include "Globals.h"
#include "LittleEngine.h"
#include "ModuleWindow.h"

ModuleWindow::~ModuleWindow()
{
	CleanUp();
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

		if (FULLSCREEN_DESKTOP)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		else if (FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (resizableEnabled)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}
		if (borderlessEnabled)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		InitOpenGLAttributes();
		SDL_DisplayMode DM;
		SDL_GetDesktopDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;
		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, flags);

		if (window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface

			screen_surface = SDL_GetWindowSurface(window);
		}
	}
	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");
	//Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::WindowResized(unsigned width, unsigned height)
{
	this->width = static_cast<int>(width);
	this->height = static_cast<int>(height);
	float aspect = static_cast<float>(width) / static_cast<float>(height);
	Engine->moduleCamera->SetAspectRatio(aspect);
	SDL_SetWindowSize(window, width, height);
	glViewport(0, 0, width, height);
}


void ModuleWindow::SetWindowMode(int windowMode) {
	if (windowMode == 0) {
		SDL_SetWindowFullscreen(window, 0);
	}
	if (windowMode == 1) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	}
	if (windowMode == 2) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
}

void ModuleWindow::SetResizable(bool resizable) {
	this->resizableEnabled = resizable;
	SDL_bool sdlResizable = resizableEnabled ? SDL_TRUE : SDL_FALSE;
	SDL_SetWindowResizable(window, sdlResizable);

}
void ModuleWindow::SetBorderless(bool borderless) {
	this->borderlessEnabled = borderless;
	SDL_bool sdlborderer = borderlessEnabled ? SDL_TRUE : SDL_FALSE;
	SDL_SetWindowBordered(window, sdlborderer);
}

void ModuleWindow::SetBrightness(float brightness) {
	this->brightness = brightness;
	SDL_SetWindowBrightness(window, brightness);
}

void ModuleWindow::InitOpenGLAttributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
	// Request a debug context.
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG
	);
}