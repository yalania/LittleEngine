#include "UI.h"
#include "../imgui/imgui.h"
#include "../Log.h"
#include "../imgui/imgui_internal.h"
#include "../Utils/SystemProperties.h"


namespace UIState {
	bool showingDebugWindow = false;
	bool showingAboutWindow = false;
	bool showingPropertiesWindow = false;
	bool showingTimeControlWindow = false;
	bool showingTextureInfo = false;
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
namespace FrameOptions {
	int numberOfFramesToAdvance = SCREEN_FPS;
}
namespace System{
	SystemProperties systemProperties;
}
namespace Geometry {
	bool showCheckerboardTexture = false;
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

		ImGui::Text("SDL Version:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 0, 1, 1), System::systemProperties.GetSDLVersion().c_str());
		ImGui::Text("OpenGL Available Version:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 0, 1, 1), System::systemProperties.GetOpenGLAvailableVersion().c_str());
		ImGui::Text("OpenGL Version:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 0, 1, 1), System::systemProperties.GetOpenGLCurrentVersion().c_str());
		ImGui::Separator();
		ImGui::Text("CPUs:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 1, 0, 1), System::systemProperties.GetSystemCPUs().c_str());
		ImGui::Text("System RAM:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 1, 0, 1), (std::to_string(System::systemProperties.GetSystemRam()) + " Gb").c_str());
		ImGui::Text("Caps:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 1, 0, 1), System::systemProperties.GetSystemCaps().c_str());
		ImGui::Separator();
		ImGui::Text("GPU:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 1, 0, 1), System::systemProperties.GetSystemGPU().c_str());
		ImGui::Text("GPU Vendor:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 1, 0, 1), System::systemProperties.GetSystemGPUBrand().c_str());
		ImGui::Text("VRAM Budget:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 1, 0, 1), (std::to_string(System::systemProperties.GetVRAMBudget()) + " Mb").c_str());
		ImGui::Text("VRAM Usage:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 1, 0, 1), (std::to_string(System::systemProperties.GetVRAMUsage()) + " Mb").c_str());
		ImGui::Text("VRAM Available:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 1, 0, 1), (std::to_string(System::systemProperties.GetVRAMAvailable()) + " Mb").c_str());
		ImGui::Text("VRAM Reserved:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(1, 1, 0, 1), (std::to_string(System::systemProperties.GetVRAMReserved()) + " Mb").c_str());
		ImGui::Separator();
		char title[25];
		sprintf_s(title, 25, "Framerate %1.f", Engine->moduleTimeController->frameRateLog[60]);
		ImGui::PlotHistogram("##frameRate", &Engine->moduleTimeController->frameRateLog[0], 59, 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		ImGui::Text("Delta time value: %f ", Engine->moduleTimeController->deltaTime);
	}
}

void UI::GeometryPropertiesTab() {
	ImGui::Begin("Model properties");

	const Entity &entity = Engine->moduleRenderer->GetEntity();
	ImGui::Text("Transform:");
	ImGui::DragFloat3("Position",  &entity.entityTransform->position[0],NULL, NULL, NULL);
	ImGui::DragFloat3("Rotation", &entity.entityTransform->rotation[0], NULL, NULL, NULL);
	ImGui::DragFloat3("Scale", &entity.entityTransform->scale[0], NULL, NULL, NULL);

	ImGui::Separator();
	ImGui::Text("Triangle count:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.5, 0.5, 1, 1), std::to_string(entity.entityModel->totalTriangleCount).c_str());
	ImGui::Text("Vertex count:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.5, 0.5, 1, 1), std::to_string(entity.entityModel->totalVertexCount).c_str());
	ImGui::Text("Meshes count:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.5, 0.5, 1, 1), std::to_string(entity.entityModel->meshes.size()).c_str());

	ImGui::Separator();
	for (auto & texture : entity.entityModel->GetTextureInfo()) {
		ImGui::Text("Texture name:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.5, 0.5, 1, 1), texture->path.c_str());
		ImGui::Text("Texture type:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.5, 0.5, 1, 1), texture->type.c_str());
		ImGui::Text("Texture storage:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.5, 0.5, 1, 1), std::to_string(texture->textureSize).c_str());
	}
	ImGui::Checkbox("Axis Align Bouding Box", &entity.entityModel->activateBoudingBox);
	ImGui::SameLine();
	if (ImGui::Checkbox("Checker Texture", &Geometry::showCheckerboardTexture)) {
		entity.entityModel->ShowCheckerBoardTexture(Geometry::showCheckerboardTexture);
	}
	ImGui::End();
}

void UI::InputPropertiesTab() {

	if (ImGui::CollapsingHeader("Input"))
	{
		ImGuiIO& io = ImGui::GetIO();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse pos: <INVALID>");
		ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
		ImGui::Text("Mouse down:");     for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (io.MouseDownDuration[i] >= 0.0f) { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
		ImGui::Text("Mouse clicked:");  for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseClicked(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
		ImGui::Text("Mouse dbl-clicked:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseDoubleClicked(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
		ImGui::Text("Mouse released:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseReleased(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
		ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);

		ImGui::Text("Keys down:");      for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (io.KeysDownDuration[i] >= 0.0f) { ImGui::SameLine(); ImGui::Text("%d (0x%X) (%.02f secs)", i, i, io.KeysDownDuration[i]); }
		ImGui::Text("Keys pressed:");   for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (ImGui::IsKeyPressed(i)) { ImGui::SameLine(); ImGui::Text("%d (0x%X)", i, i); }
		ImGui::Text("Keys release:");   for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (ImGui::IsKeyReleased(i)) { ImGui::SameLine(); ImGui::Text("%d (0x%X)", i, i); }
		ImGui::Text("Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
		ImGui::Text("Chars queue:");    for (int i = 0; i < io.InputQueueCharacters.Size; i++) { ImWchar c = io.InputQueueCharacters[i]; ImGui::SameLine();  ImGui::Text("\'%c\' (0x%04X)", (c > ' ' && c <= 255) ? (char)c : '?', c); } // FIXME: We should convert 'c' to UTF-8 here but the functions are not public.
	}
}