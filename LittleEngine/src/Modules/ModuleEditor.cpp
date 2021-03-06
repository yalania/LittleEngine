#include"ModuleEditor.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

#include "LittleEngine.h"
#include <Modules/ModuleWindow.h>

bool ModuleEditor::Init() {
	LOG("Init IMGUI sytem");
	SDL_GLContext glcontext = ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(Engine->moduleWindow->window, glcontext);
	return ImGui_ImplOpenGL3_Init("#version 330");
}

UpdateStatus ModuleEditor::PreUpdate() {

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(Engine->moduleWindow->window);
	ImGui::NewFrame();
	return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleEditor::Update() {	
	return mGeneralUI.ShowUI();
}


UpdateStatus ModuleEditor::PostUpdate() {

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return UpdateStatus::UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}
