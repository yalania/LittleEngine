#include "UI.h"
#include "../imgui/imgui.h"
#include "../Log.h"
#include "../LittleEngine.h"
#include "../imgui/imgui_internal.h"


namespace UIState {
	bool showingDebugWindow = false;
	bool showingAboutWindow = false;
	bool showingPropertiesWindow = false;
}

namespace WindowOptions {
	bool showingDebugWindow = false;
	bool showingAboutWindow = false;
	bool showingPropertiesWindow = false;
}

namespace CameraOptions {
	bool frustumCulling = true;
	bool isActiveCamera = true;
}

void UI::ShowUI() {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("LittleEngine"))
		{
			ImGui::MenuItem("Properties", NULL, &UIState::showingPropertiesWindow);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::BeginMenu("Projection..."))
			{
				bool perspectiveEnable = Engine->moduleCamera->perspectiveEnable;
				if (ImGui::MenuItem("Orthographic ", nullptr, !perspectiveEnable, perspectiveEnable))
				{
					Engine->moduleCamera->EnableOrthographic();

				}
				if (ImGui::MenuItem("perspective", nullptr, perspectiveEnable, !perspectiveEnable))
				{
					Engine->moduleCamera->EnablePerspective();

				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		ImGui::MenuItem("Debug", NULL, &UIState::showingDebugWindow);
		ImGui::MenuItem("About", NULL, &UIState::showingAboutWindow);
		ImGui::EndMainMenuBar();
	}

	UpdateState();
	//ImGui::ShowDemoWindow();
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
	ImGui::BeginTabItem("Console");
	if (!getLogData()->empty()) {
		ImGui::TextUnformatted(getLogData()->begin());
		//ImGui::SetScrollHere(1.0f);
	}
	ImGui::EndTabItem();
	ImGui::EndTabBar();
	ImGui::End();
}

void UI::DrawAboutWindow() {
	ImGui::Begin("About");
	ImGui::Text("LittleEngine");
	ImGui::Text("An Engine done for learning");
	ImGui::Text("Author: Anabel Hernández Barrera");
	ImGui::Text("Libraries:");
	ImGui::Text("\t* GLM v0.9.9.6 ");
	ImGui::Text("\t* IMGUI v1.73 ");
	ImGui::Text("\t* stb_image v2.23 ");
	ImGui::Text("License: MIT License");
	ImGui::End();

}

void UI::DrawPropertiesWindow() {
	ImGui::Begin("Properties");
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Checkbox("Active", &CameraOptions::isActiveCamera);
		ImGui::SliderFloat("Mov.Speed", &Engine->moduleCamera->cameraSpeed, 0.05f, 2.0f);
		if (ImGui::SliderFloat("Near Plane", &Engine->moduleCamera->nearPlane, 0.0f, 200.0f)) {
			Engine->moduleCamera->LoadProjection();
		}
		if (ImGui::SliderFloat("Far Plane", &Engine->moduleCamera->farPlane, 0.0f, 200.0f)) {
			Engine->moduleCamera->LoadProjection();
		}
		if(ImGui::SliderFloat("Aspect ratio", &Engine->moduleCamera->aspect, -10.0f, 10.0f) ){
			Engine->moduleCamera->LoadProjection();
		}
		if (ImGui::SliderFloat("Fov ratio", &Engine->moduleCamera->frustumFov, 0.0f, 179.9f)) {
			Engine->moduleCamera->LoadProjection();
		}
		ImGui::Checkbox("Frustum Culling", &CameraOptions::frustumCulling);
	}
	if (ImGui::CollapsingHeader("Window"))
	{
		if (ImGui::SliderFloat("Width", &Engine->moduleWindow->width, SCREEN_WIDTH, 1920.0f)) {
			Engine->moduleWindow->WindowResized(Engine->moduleWindow->width, Engine->moduleWindow->height);
		}
		if (ImGui::SliderFloat("Heigth", &Engine->moduleWindow->height, SCREEN_HEIGHT, 100.0f)) {
			Engine->moduleWindow->WindowResized(Engine->moduleWindow->width, Engine->moduleWindow->height);
		}
	}
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
}