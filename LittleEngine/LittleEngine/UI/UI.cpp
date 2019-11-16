#include "UI.h"
#include "../imgui/imgui.h"
#include "../Log.h"
#include "../LittleEngine.h"
#include "../imgui/imgui_internal.h"


namespace UIState {
	bool showingDebugWindow = false;
	bool showingAboutWindow = false;
	bool showingPropertiesWindow = false;
	bool showingTimeControlWindow = false;
}

namespace WindowOptions {
	bool showingDebugWindow = false;
	bool showingPropertiesWindow = false;
	bool fullScreen = FULLSCREEN;
	bool fullScreenDesktop = FULLSCREEN_DESKTOP;
	bool rezisable = RESIZABLE;
	bool borderless = BORDERLESS;
	float brightness = BRIGHTNESS;
}

namespace CameraOptions {
	bool frustumCulling = true;
	bool isActiveCamera = true;
	float verticalFov;
}
namespace FrameOptions {
	int numberOfFramesToAdvance = SCREEN_FPS;
}

void UI::ShowUI() {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("LittleEngine"))
		{
			ImGui::MenuItem("Properties", NULL, &UIState::showingPropertiesWindow);

			if (ImGui::MenuItem("Load Default Model", NULL)) {
				Engine->moduleRenderer->AddEntity("BakerHouse.fbx");
			}
			ImGui::MenuItem("About", NULL, &UIState::showingAboutWindow);
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
		ImGui::MenuItem("Time Control", NULL, &UIState::showingTimeControlWindow);
		ImGui::MenuItem("Debug", NULL, &UIState::showingDebugWindow);
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
	ImGui::Text("An Engine done for learning");
	ImGui::Text("Author: Anabel Hern�ndez Barrera");
	ImGui::Text("Libraries:");
	ImGui::Text("\t* GLM v0.9.9.6 ");
	ImGui::Text("\t* IMGUI v1.73 ");
	ImGui::Text("\t* stb_image v2.23 ");
	ImGui::Text("License: MIT License");
	ImGui::End();

}

void UI::DrawPropertiesWindow() {
	ImGui::Begin("Configuration");
	CameraPropertiesTab();
	WindowPropertiesTab();
	SystemPropertiesTab();

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

	char title[35];
	sprintf_s(title, 25, "Forward %d frames",FrameOptions::numberOfFramesToAdvance);
	if (ImGui::Button(title))
	{
		Engine->moduleTimeController->AdvanceFrames(FrameOptions::numberOfFramesToAdvance);
	}
	ImGui::SliderInt("Frames to advance", &FrameOptions::numberOfFramesToAdvance, 1, 100);
	ImGui::End();
}

void UI::CameraPropertiesTab() {
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::SliderFloat("Mov.Speed", &Engine->moduleCamera->cameraSpeed, CAMERA_SPEED, CAMERA_MAX_SPEED);
		if (ImGui::SliderFloat("Near Plane", &Engine->moduleCamera->nearPlane, 0.0f, MAX_PLANE)) {
			Engine->moduleCamera->UpdateProjection();
		}
		if (ImGui::SliderFloat("Far Plane", &Engine->moduleCamera->farPlane, 0.0f, MAX_PLANE)) {
			Engine->moduleCamera->UpdateProjection();
		}
		if (ImGui::SliderFloat("Aspect ratio", &Engine->moduleCamera->aspect, -10.0f, 10.0f)) {
			Engine->moduleCamera->UpdateProjection();
		}
		if (ImGui::SliderFloat("Horizontal Fov ratio", &Engine->moduleCamera->frustumFov, 0.0f, 179.9f)) {
			Engine->moduleCamera->UpdateProjection();
		}
		if (ImGui::Checkbox("Perspective enable", &Engine->moduleCamera->perspectiveEnable)) {
			Engine->moduleCamera->UpdateProjection();
		}

	}
}

void UI::WindowPropertiesTab() {
	if (ImGui::CollapsingHeader("Window"))
	{
		if (ImGui::SliderFloat("Brightness", &WindowOptions::brightness, 0.0f, 5.0f)) {
			Engine->moduleWindow->SetBrightness(WindowOptions::brightness);
		}
		if (ImGui::SliderInt("Width", &Engine->moduleWindow->width, SCREEN_WIDTH, 1920)) {
			Engine->moduleWindow->WindowResized(Engine->moduleWindow->width, Engine->moduleWindow->height);
		}
		if (ImGui::SliderInt("Heigth", &Engine->moduleWindow->height, SCREEN_HEIGHT, 100)) {
			Engine->moduleWindow->WindowResized(Engine->moduleWindow->width, Engine->moduleWindow->height);
		}
		if (ImGui::Checkbox("FullScreen", &WindowOptions::fullScreen)) {
			Engine->moduleWindow->SetFullScreen(WindowOptions::fullScreen);
			WindowOptions::fullScreenDesktop = false;
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Full desktop", &WindowOptions::fullScreenDesktop)) {
			Engine->moduleWindow->SetFullScreenDesktop(WindowOptions::fullScreenDesktop);
			WindowOptions::fullScreen = false;
		}
		if (ImGui::Checkbox("Borderless", &WindowOptions::borderless)) {
			Engine->moduleWindow->SetBorderless(WindowOptions::borderless);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Resizable", &WindowOptions::rezisable)) {
			Engine->moduleWindow->SetResizable(WindowOptions::rezisable);
		}
	}
}

void UI::SystemPropertiesTab() {
	if (ImGui::CollapsingHeader("System information"))
	{
		char title[25];
		sprintf_s(title, 25, "Framerate %1.f", Engine->moduleTimeController->frameRateLog[60]);
		ImGui::PlotHistogram("##frameRate", &Engine->moduleTimeController->frameRateLog[0], 60, 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		ImGui::Text("Delta time value: %f ", Engine->moduleTimeController->deltaTime);
	}
}