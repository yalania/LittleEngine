#include "UI.h"
#include "../imgui/imgui.h"
#include "../Log.h"
#include "../LittleEngine.h"
#include "../imgui/imgui_internal.h"

void UI::ShowUI() {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load Texture"))
			{
				ImGui::OpenPopup("Some Popup");
			}
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
		ImGui::EndMainMenuBar();
	}

	TabExample();
}


void UI::TabExample() {
	ImGui::BeginTabBar("Tab Bar");
	DrawConsoleWindow();
	DrawActivityWindow();
	ImGui::EndTabBar();
}


void UI::DrawConsoleWindow() {
	if (ImGui::BeginTabItem("Console")) {
		if (!getLogData()->empty()) {
			ImGui::TextUnformatted(getLogData()->begin());
			//ImGui::SetScrollHere(1.0f);
		}
		ImGui::EndTabItem();
	}
}

void UI::DrawActivityWindow() {
	if (ImGui::BeginTabItem("About")) {
		ImGui::Text("LittleEngine");
		ImGui::Text("An Engine done for learning");
		ImGui::Text("Author: Anabel Hernández Barrera");
		ImGui::Text("Libraries:");
		ImGui::Text("\t* GLM v0.9.9.6 ");
		ImGui::Text("\t* IMGUI v1.73 ");
		ImGui::Text("\t* stb_image v2.23 ");
		ImGui::Text("License: MIT License");
		ImGui::EndTabItem();
	}
}
