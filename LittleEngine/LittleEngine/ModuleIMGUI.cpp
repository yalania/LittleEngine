#include"ModuleIMGUI.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

#include "ModuleWindow.h"
#include "LittleEngine.h"

bool ModuleIMGUI::Init() {
	LOG("Init IMGUI sytem");
	SDL_GLContext glcontext = ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(Engine->moduleWindow->window, glcontext);
	return ImGui_ImplOpenGL3_Init("#version 330");
}

update_status ModuleIMGUI::PreUpdate() {

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(Engine->moduleWindow->window);
	ImGui::NewFrame();
	return UPDATE_CONTINUE;
}

update_status ModuleIMGUI::Update() {

	ImGui::BeginTabBar("Settings#left_tabs_bar");

	DrawConsoleWindow();
	if (ImGui::BeginTabItem("About")) {
		ImGui::Text("LittleEngine");
		ImGui::Text("An Engine done for learning");
		ImGui::Text("Author: Anabel Hern�ndez Barrera");
		ImGui::Text("Libraries:");
		ImGui::Text("\t* GLM v0.9.9.6 ");
		ImGui::Text("\t* IMGUI v1.73 ");
		ImGui::Text("\t* stb_image v2.23 ");
		ImGui::Text("License: MIT License");
		ImGui::EndTabItem();
	}
	ImGui::EndTabBar();
	return UPDATE_CONTINUE;
}


update_status ModuleIMGUI::PostUpdate() {

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return UPDATE_CONTINUE;
}

bool ModuleIMGUI::CleanUp() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}

void ModuleIMGUI::DrawConsoleWindow() {
	if (ImGui::BeginTabItem("Console")) {
		if (!getLogData()->empty()) {
			ImGui::TextUnformatted(getLogData()->begin());
			ImGui::SetScrollHere(1.0f);
		}
		ImGui::EndTabItem();
	}
}