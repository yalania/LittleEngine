#include "PropertiesUI.h"
#include "../Utils/SystemProperties.h"
#include "../imgui/imgui.h"
#include <LittleEngine.h>
#include <Modules/ModuleWindow.h>

namespace WindowOptions {
	bool showingDebugWindow = false;
	bool showingPropertiesWindow = false;
	bool rezisable = RESIZABLE;
	bool borderless = BORDERLESS;
	float brightness = BRIGHTNESS;
}

namespace System {
	SystemProperties systemProperties;
}

namespace Renderer {
	bool faceCullingEnabled = true;
	bool clockwisefaceCullingEnabled = false;
}

void PropertiesUI::DrawPropertiesWindow() {
	ImGui::Begin("Configuration");
	CameraPropertiesTab();
	WindowPropertiesTab();
	SystemPropertiesTab();
	InputPropertiesTab();
	RenderPropertiesTab();

	ImGui::End();
}

void PropertiesUI::CameraPropertiesTab() {

		float nearPlane = Engine->moduleCamera->GetNearPlane();
		float aspect = Engine->moduleCamera->GetAspectRatio();
		float farPlane = Engine->moduleCamera->GetFarPlane();
		float horizontalFov = Engine->moduleCamera->GetHorizontalFov();
		bool perspectiveEnable = Engine->moduleCamera->GetPerspectiveEnable();

	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::SliderFloat("Keys Mov. Speed", &Engine->moduleCamera->cameraSpeedKeys, CAMERA_SPEED, CAMERA_MAX_SPEED);
		ImGui::SliderFloat("Mouse Mov. Speed", &Engine->moduleCamera->cameraSpeedMouse, CAMERA_SPEED, CAMERA_MAX_SPEED);
		if (ImGui::SliderFloat("Near Plane", &nearPlane, 0.0f, MAX_PLANE)) {
			Engine->moduleCamera->SetNearPlane(nearPlane);
		}
		if (ImGui::SliderFloat("Far Plane", &farPlane, 0.0f, MAX_PLANE)) {
			Engine->moduleCamera->SetFarPlane(farPlane);
		}
		if (ImGui::SliderFloat("Aspect ratio", &aspect, -10.0f, 10.0f)) {
			Engine->moduleCamera->SetAspectRatio(aspect);
		}
		if (ImGui::SliderFloat("Horizontal Fov ratio", &horizontalFov, 0.0f, 179.9f)) {
			Engine->moduleCamera->SetHorizontalFov(horizontalFov);
		}
		if (ImGui::Checkbox("Perspective enable", &perspectiveEnable)) {
			Engine->moduleCamera->SetPerspectiveEnable(perspectiveEnable);
		}

	}
}

void PropertiesUI::WindowPropertiesTab() {
	if (ImGui::CollapsingHeader("Window"))
	{
		if (ImGui::SliderFloat("Brightness", &WindowOptions::brightness, 0.0f, 5.0f)) {
			Engine->moduleWindow->SetBrightness(WindowOptions::brightness);
		}
		int windowWidth = Engine->moduleWindow->GetWidth();
		int windowHeight = Engine->moduleWindow->GetHeight();
		if (ImGui::SliderInt("Width", &windowWidth, SCREEN_WIDTH, 1920)) {
			Engine->moduleWindow->SetWindowSize(windowWidth, windowHeight);
		}
		if (ImGui::SliderInt("Heigth", &windowHeight, SCREEN_HEIGHT, 100)) {
			Engine->moduleWindow->SetWindowSize(windowWidth, windowHeight);
		}
		static int selectedMode = 0;
		if (ImGui::Combo("Filling mode", &selectedMode, "Windowed\0FullScreen\0Full Desktop")) {
			Engine->moduleWindow->SetWindowMode(selectedMode);
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

void PropertiesUI::SystemPropertiesTab() {
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

void PropertiesUI::InputPropertiesTab() {

	if (ImGui::CollapsingHeader("Input"))
	{
		ImGuiIO& io = ImGui::GetIO();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse pos: <INVALID>");

		ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
		ImGui::Separator();
		ImGui::Text("Mouse down:");     for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (io.MouseDownDuration[i] >= 0.0f) { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
		ImGui::Text("Mouse clicked:");  for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseClicked(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
		ImGui::Text("Mouse dbl-clicked:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseDoubleClicked(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
		ImGui::Text("Mouse released:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseReleased(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
		ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);
		ImGui::Separator();
		ImGui::Text("Keys down:");      for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (io.KeysDownDuration[i] >= 0.0f) { ImGui::SameLine(); ImGui::Text("%d (0x%X) (%.02f secs)", i, i, io.KeysDownDuration[i]); }
		ImGui::Text("Keys pressed:");   for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (ImGui::IsKeyPressed(i)) { ImGui::SameLine(); ImGui::Text("%d (0x%X)", i, i); }
		ImGui::Text("Keys release:");   for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (ImGui::IsKeyReleased(i)) { ImGui::SameLine(); ImGui::Text("%d (0x%X)", i, i); }
	}
}

void PropertiesUI::RenderPropertiesTab() {
	if (ImGui::CollapsingHeader("Render properties"))
	{
		static int selectedMode = 0;
		if (ImGui::Combo("Filling mode", &selectedMode, "Fill\0Lines\0Points")) {
			Engine->moduleRenderer->SelectFillingMode(selectedMode);
		}
		if (ImGui::Checkbox("Enable Face culling", &Renderer::faceCullingEnabled)) {
			Engine->moduleRenderer->EnableFaceCulling(Renderer::faceCullingEnabled);
		}
		if (ImGui::Checkbox("Enable Clockwise Face culling", &Renderer::clockwisefaceCullingEnabled)) {
			Engine->moduleRenderer->EnableClockwiseFaceCulling(Renderer::clockwisefaceCullingEnabled);
		}
	}
}