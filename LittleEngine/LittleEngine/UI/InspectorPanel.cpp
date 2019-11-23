#include "InspectorPanel.h"
#include "../imgui/imgui.h"

void InspectorPanel::ShowGameObjectInfo(GameObject & gameObject) const {
	ImGui::Begin("Hierarchy Panel");


	ImGui::Separator();
	ImGui::Text("Transform");
	ImGui::Text("Position"); ImGui::SameLine();
	ImGui::DragFloat("X", &gameObject.transform.position.x, NULL, NULL, NULL); ImGui::SameLine();
	ImGui::DragFloat("Y", &gameObject.transform.position.y, NULL, NULL, NULL); ImGui::SameLine();
	ImGui::DragFloat("Z", &gameObject.transform.position.z, NULL, NULL, NULL);
	ImGui::Text("Rotation"); ImGui::SameLine();
	ImGui::DragFloat("rX", &gameObject.transform.rotation.x, NULL, NULL, NULL); ImGui::SameLine();
	ImGui::DragFloat("rY", &gameObject.transform.rotation.y, NULL, NULL, NULL); ImGui::SameLine();
	ImGui::DragFloat("rZ", &gameObject.transform.rotation.z, NULL, NULL, NULL);
	ImGui::Text("Scae"); ImGui::SameLine();
	ImGui::DragFloat("sX", &gameObject.transform.scale.x, NULL, NULL, NULL); ImGui::SameLine();
	ImGui::DragFloat("sY", &gameObject.transform.scale.y, NULL, NULL, NULL); ImGui::SameLine();
	ImGui::DragFloat("sZ", &gameObject.transform.scale.z, NULL, NULL, NULL);
	ImGui::Separator();

	ImGui::End();
}