#include "UI.h"
#include "../Log.h"
#include "../imgui/imgui_internal.h"

namespace UIState {
	bool showingDebugWindow = false;
	bool showingAboutWindow = false;
	bool showingPropertiesWindow = false;
	bool showingTimeControlWindow = false;
	bool showingTextureInfo = false;
}
namespace FrameOptions {
	int numberOfFramesToAdvance = SCREEN_FPS;
}

update_status UI::ShowUI() {
	update_status updateStatus = UPDATE_CONTINUE;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("LittleEngine"))
		{

			if (ImGui::MenuItem("Load Default Model", NULL)) {
				Engine->moduleRenderer->AddEntity("BakerHouse.fbx");
			}
			ImGui::MenuItem("Properties", NULL, &UIState::showingPropertiesWindow);
			ImGui::MenuItem("About", NULL, &UIState::showingAboutWindow);
			if (ImGui::MenuItem("Quit")) {
				updateStatus = UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Show Texture Properties Window", NULL, &UIState::showingTextureInfo);
			ImGui::MenuItem("Show Time Control Window", NULL, &UIState::showingTimeControlWindow);
			ImGui::MenuItem("Show Debug Window", NULL, &UIState::showingDebugWindow);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (UIState::showingTextureInfo) {
		GeometryPropertiesTab();
	}
	UpdateState();
	return updateStatus;
}


void UI::TabExample() {
	ImGui::BeginTabBar("Tab Bar");
	DrawConsoleWindow();
	DrawAboutWindow();
	ImGui::EndTabBar();
}


void UI::DrawConsoleWindow() {

	ImGui::Begin("Debug");
	ImGui::BeginTabBar("Debug");
	if (ImGui::BeginTabItem("Console")) {
		if (!getLogData()->empty()) {
			ImGui::TextUnformatted(getLogData()->begin());
			//ImGui::SetScrollHere(1.0f);
		}
	ImGui::EndTabItem();
	}
	ImGui::EndTabBar();
	ImGui::End();
}

void UI::DrawAboutWindow() {
	ImGui::Begin("About");
	ImGui::Text("LittleEngine");
	ImGui::Text("An Engine done for UPC Videogames Master");
	ImGui::Text("Author: Anabel Hernández Barrera");
	ImGui::Text("Libraries:");
	ImGui::BulletText("GLM v0.9.9.6 ");
	ImGui::BulletText("IMGUI v1.73 ");
	ImGui::BulletText("stb_image v2.23 ");
	ImGui::BulletText("Assimp v5.0.0 ");
	ImGui::Text("License: MIT License");
	ImGui::Text("For more information visit:");
	if (ImGui::Button("GitHub Page")) {
		ShellExecuteA(NULL, "open", "https://github.com/yalania/LittleEngine", NULL, NULL, SW_SHOWNORMAL);
	}
	ImGui::End();

}

void UI::DrawPropertiesWindow() {
	ImGui::Begin("Configuration");
	CameraPropertiesTab();
	WindowPropertiesTab();
	SystemPropertiesTab();
	InputPropertiesTab();
	RenderPropertiesTab();

	ImGui::End();
}

void UI::UpdateState() {

	if (UIState::showingAboutWindow) {
		DrawAboutWindow();
	}
	if (UIState::showingDebugWindow) {
		DrawConsoleWindow();
	}
	if (UIState::showingPropertiesWindow) {
		DrawPropertiesWindow();
	}
	if (UIState::showingTimeControlWindow) {
		TimeControlButtons();
	}
}

void UI::TimeControlButtons() {
	ImGui::Begin("Time Control");
	if (ImGui::Button("Play"))
	{
		Engine->moduleTimeController->Play();
	}

	if (ImGui::Button("Pause"))
	{
		Engine->moduleTimeController->Pause();
	}

	ImGui::SliderInt("", &FrameOptions::numberOfFramesToAdvance, 1, 100);
	char title[35];
	sprintf_s(title, 25, "Forward %d frames",FrameOptions::numberOfFramesToAdvance);
	if (ImGui::Button(title))
	{
		Engine->moduleTimeController->AdvanceFrames(FrameOptions::numberOfFramesToAdvance);
	}
	ImGui::End();
}
