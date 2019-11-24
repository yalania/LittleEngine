#include "InspectorPanel.h"
#include "../imgui/imgui.h"
#include "../LittleEngine.h"

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

		for (auto & component : gameObject->components) {
			ShowComponentInfo(*component);
		}


		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::SetCursorPosX((ImGui::GetWindowWidth() / 2 - 50));
		if (ImGui::Button("Add component")) {
			ImGui::OpenPopup("Components_chooser");
		}
		AddNewComponent();
	}
	ImGui::End();


}


void InspectorPanel::ShowComponentInfo(Component & component) {
	ImGui::Separator();
	switch (component.type)
	{
	case ComponentType::MESH:
		ShowMeshComponentInfo(static_cast<Mesh&>(component));
		break;
	}
	ImGui::Separator();
}

void  InspectorPanel::AddNewComponent() {

	
	if (ImGui::BeginPopup("Components_chooser"))
	{

		const char * components = "Mesh\0Texture\0Collider";
		static int selectedComponent = 0;
		ImGui::Combo("Component", &selectedComponent, components);
		if (ImGui::Button("Accept"))
		{
			switch (selectedComponent)
			{
			case 0 :
				Engine->moduleRenderer->AddMeshComponentToGameObject(gameObject);
				break;
			case 1:
				break;
			case 2:
				break;
			}
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

void InspectorPanel::ShowMeshComponentInfo(Mesh & mesh) {

	ImGui::Text("Mesh");
	ImGui::Text(mesh.meshInfo.meshName.c_str());
	ImGui::Text("Triangle count:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.5, 0.5, 1, 1), std::to_string(mesh.meshInfo.numberOfTriangles).c_str());
	ImGui::Text("Vertex count:"); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.5, 0.5, 1, 1), std::to_string(mesh.meshInfo.numberOfVertex).c_str());
}