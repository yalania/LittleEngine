#include "InspectorPanel.h"
#include "../imgui/imgui.h"

void InspectorPanel::ShowGameObjectInfo() {
	ImGui::Begin("Inspector");
	if (gameObject != nullptr) {
		writable.erase(writable.begin(), writable.end());
		std::copy(gameObject->name.begin(), gameObject->name.end(), std::back_inserter(writable));
		writable.push_back('\0');
		if (ImGui::InputText("", &writable[0], 20)) {
			gameObject->name = std::string(&writable[0]);
		}

		ImGui::Separator();
		ImGui::Text("Transform");
		ImGui::Text("Position: "); ImGui::SameLine();  ImGui::DragFloat3("##Position", &gameObject->transform.position[0], NULL, NULL, NULL); ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Text("Rotation: "); ImGui::SameLine();  ImGui::DragFloat3("##Rotation", &gameObject->transform.rotation[0], NULL, NULL, NULL); ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Text("Scale:    "); ImGui::SameLine();  ImGui::DragFloat3("##Scale", &gameObject->transform.scale[0], NULL, NULL, NULL); ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Separator();



		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::SetCursorPosX((ImGui::GetWindowWidth() / 2 - 50));
		if (ImGui::Button("Add component")) {

		}
	}
	ImGui::End();
}


void InspectorPanel::ShowComponentInfo(Component & component) {

}

void  InspectorPanel::AddNewComponent() {

}