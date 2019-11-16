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
	keyboard = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event))
	{
		//ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT || keyboard[SDL_SCANCODE_ESCAPE])
		{
			return UPDATE_STOP;
		}
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) 
		{
			Engine->moduleWindow->WindowResized(event.window.data1, event.window.data2);
		}
		CameraMovementWithMouse(event);
		if (event.type == SDL_DROPFILE) {      // In case if dropped file
			char* dropped_filedir = event.drop.file;
			Engine->moduleRenderer->AddEntity(dropped_filedir);
			// Shows directory of dropped file
			SDL_free(dropped_filedir);    // Free dropped_filedir memory
			Engine->moduleCamera->FocusOnEntity(Engine->moduleRenderer->GetEntity());
			break;
		}
	}
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
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftMouseButtonIsDown = true;
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
		if (event.button.button == SDL_BUTTON_LEFT) {
			leftMouseButtonIsDown = false;
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
	if (event.type == SDL_MOUSEMOTION) {
			currentMousePositionOffset.x = static_cast<float>((lastMousePosition.x - event.motion.x) *mouseSensitivity);
			currentMousePositionOffset.y = static_cast<float>((lastMousePosition.y - event.motion.y) *mouseSensitivity);

			lastMousePosition.x = static_cast<float>(event.motion.x);
			lastMousePosition.y = static_cast<float>(event.motion.y);
			if (rightMouseButtonIsDown) {
				Engine->moduleCamera->MoveCameraWithMousePosition(currentMousePositionOffset);
			}
			if (middleMouseButtonIsDown) {
				Engine->moduleCamera->Translate(glm::vec3(currentMousePositionOffset,0.0f));
			}
	}
}

void ModuleInput::CameraMovementWithKeys() {

	glm::vec3 translationDirection = glm::vec3(0.0f);
	if (keyboard[SDL_SCANCODE_Q]) {
		translationDirection.y = 1.0f;
	}
	if (keyboard[SDL_SCANCODE_A]) {
		translationDirection.x = -1.0f;
	}
	if (keyboard[SDL_SCANCODE_E]) {
		translationDirection.y = -1.0f;
	}
	if (keyboard[SDL_SCANCODE_D]) {
		translationDirection.x = 1.0f;
	}
	if (keyboard[SDL_SCANCODE_W]) {
		translationDirection.z = -1.0f;
	}
	if (keyboard[SDL_SCANCODE_S]) {
		translationDirection.z = 1.0f;
	}
	if (translationDirection != glm::vec3(0.0f)) {
		Engine->moduleCamera->Translate(translationDirection);
	}
	if (keyboard[SDL_SCANCODE_LSHIFT] && !shiftButtonIsDown) {
		cameraPreviousSpeed = Engine->moduleCamera->cameraSpeed;
		Engine->moduleCamera->cameraSpeed *= 2.0f;
		shiftButtonIsDown = true;
	}
	else if(shiftButtonIsDown) {
		shiftButtonIsDown = false;
		Engine->moduleCamera->cameraSpeed = cameraPreviousSpeed;
	}

	if (keyboard[SDL_SCANCODE_F]) {
		Engine->moduleCamera->FocusOnEntity(Engine->moduleRenderer->GetEntity());
	}

	if ((keyboard[SDL_SCANCODE_LALT] || keyboard[SDL_SCANCODE_RALT]) && leftMouseButtonIsDown) {
		Engine->moduleCamera->OrbitAroundEntity(Engine->moduleRenderer->GetEntity(), currentMousePositionOffset);
	}
}