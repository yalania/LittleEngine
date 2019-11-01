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
		CameraMovementWithMouse(event);
		

	}
	keyboard = SDL_GetKeyboardState(NULL);
	CameraMovementWithKeys();

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}


void ModuleInput::CameraMovementWithMouse(const SDL_Event & event){

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		lastMousePosition = glm::vec2(event.button.x, event.button.y);
		if (event.button.button == SDL_BUTTON_RIGHT) {
			rightMouseButtonIsDown = true;
		}
		if (event.button.button == SDL_BUTTON_MIDDLE) {
			middleMouseButtonIsDown = true;
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_RIGHT) {
			rightMouseButtonIsDown = false;
		}
		if (event.button.button == SDL_BUTTON_MIDDLE) {
			middleMouseButtonIsDown = false;
		}
	}
	if (event.type == SDL_MOUSEWHEEL) {
		if (event.wheel.y > 0) // scroll up
		{
			Engine->moduleCamera->Zoom(true);
		}
		else if (event.wheel.y < 0) // scroll down
		{
			Engine->moduleCamera->Zoom(false);
		}

	}
	if (rightMouseButtonIsDown && event.type == SDL_MOUSEMOTION) {

		int mouseXPos = (event.motion.x - lastMousePosition.x) *mouseSensitivity;
		int mouseYPos = (lastMousePosition.y - event.motion.y) *mouseSensitivity;

		lastMousePosition.x = event.motion.x;
		lastMousePosition.y = event.motion.y;
		Engine->moduleCamera->MoveCameraWithMousePosition(glm::vec2(mouseXPos, mouseYPos));
	}

	if (middleMouseButtonIsDown && event.type == SDL_MOUSEMOTION) {

		int mouseXPos = (event.motion.x - lastMousePosition.x) * mouseSensitivity;
		int mouseYPos = (event.motion.y - lastMousePosition.y) * mouseSensitivity;

		glm::vec2 translationDirection = glm::vec2(0.0f);
		lastMousePosition.x = event.motion.x;
		lastMousePosition.y = event.motion.y;
		translationDirection.x = mouseXPos;
		translationDirection.y = mouseYPos;
		Engine->moduleCamera->Translate(translationDirection);
	}
}

void ModuleInput::CameraMovementWithKeys() const {

	glm::vec2 translationDirection = glm::vec2(0.0f);
	if (keyboard[SDL_SCANCODE_UP]) {
		translationDirection.y = 1.0f;
	}
	if (keyboard[SDL_SCANCODE_RIGHT]) {
		translationDirection.x = 1.0f;
	}
	if (keyboard[SDL_SCANCODE_DOWN]) {
		translationDirection.y = -1.0f;
	}
	if (keyboard[SDL_SCANCODE_LEFT]) {
		translationDirection.x = -1.0f;
	}
	if (translationDirection != glm::vec2(0.0f)) {
		Engine->moduleCamera->Translate(translationDirection);
	}
}