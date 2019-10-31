#include "Globals.h"
#include "LittleEngine.h"
#include "ModuleInput.h"
#include <SDL/SDL.h>
#include "imgui/imgui_impl_sdl.h"

// Destructor
ModuleInput::~ModuleInput()
{
	CleanUp();
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	SDL_PumpEvents();

	SDL_Event event;
	bool done = true;
	while (SDL_PollEvent(&event))
	{
		//ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT) 
		{

		}
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(Engine->moduleWindow->window)) 
		{

		}
		if (event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(2))
		{
			initialMousePosition = glm::vec2(event.button.x, event.button.y);
			rightMouseButtonIsDown = true;
		}
		
		if(event.type == SDL_MOUSEWHEEL){
			if (event.wheel.y > 0) // scroll up
			{
				Engine->moduleCamera->Zoom(true);
			}
			else if (event.wheel.y < 0) // scroll down
			{
				Engine->moduleCamera->Zoom(false);
			}

		}
		if (event.type == SDL_MOUSEBUTTONUP && SDL_BUTTON(2))
		{
			rightMouseButtonIsDown = false;
		}
		if (rightMouseButtonIsDown && event.type == SDL_MOUSEMOTION) {

			int mouseXPos = (event.motion.x - initialMousePosition.x) *mouseSensitivity;
			int mouseYPos = (initialMousePosition.y - event.motion.y) *mouseSensitivity;

			initialMousePosition.x = event.motion.x;	
			initialMousePosition.x = event.motion.x;
			Engine->moduleCamera->Rotate(glm::vec2(mouseXPos, mouseYPos));
		}

	}
	keyboard = SDL_GetKeyboardState(NULL);

	glm::vec4 translation = glm::vec4(0.0f);
	if (keyboard[SDL_SCANCODE_UP]) {
		translation.x = 1.0f;
		Engine->moduleCamera->Translate(translation);
	}
	if (keyboard[SDL_SCANCODE_RIGHT] ) {
		translation.y = 1.0f;
		Engine->moduleCamera->Translate(translation);
	}
	if (keyboard[SDL_SCANCODE_DOWN]) {
		translation.z = 1.0f;
		Engine->moduleCamera->Translate(translation);
	}
	if (keyboard[SDL_SCANCODE_LEFT]) {
		translation.w = 1.0f;
		Engine->moduleCamera->Translate(translation);
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
