#include"ModuleIMGUI.h"


#include "imgui/imgui.h"

#include "imgui/imgui_internal.h"

#include "imgui/imgui_impl_opengl3.h"

#include <SDL/SDL.h>
#include "GL/glew.h"
#include "ModuleWindow.h"
#include "LittleEngine.h"

bool ModuleIMGUI::Init() {
	return ImGui_ImplOpenGL3_Init("4.0");
}

update_status ModuleIMGUI::PreUpdate() {
	
	return UPDATE_CONTINUE;
}

update_status ModuleIMGUI::Update() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::ShowTestWindow();
	return UPDATE_CONTINUE;
}


update_status ModuleIMGUI::PostUpdate() {

	return UPDATE_CONTINUE;
}

bool ModuleIMGUI::CleanUp() {
	ImGui_ImplOpenGL3_Shutdown();
	return true;
}