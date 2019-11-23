#include "HierarchyPanel.h"
#include "../imgui/imgui.h"
#include "../LittleEngine.h"

void HierarchyPanel::ShowHierarchyPanel() const {
	ImGui::Begin("Hierarchy Panel");
	const GameObject * sceneRoot = Engine->moduleSceneManager->GetRoot();
	ImGui::Text(sceneRoot->name.c_str());
	IterateGameObjectsTree(sceneRoot, 0);

	if (ImGui::GetIO().MouseDownOwned[1])
	{
		ImGui::OpenPopup("hierarchy_popup");
		ImGui::SameLine();
		if (ImGui::BeginPopup("hierarchy_popup"))
		{
			if (ImGui::Selectable("Create empty")) {
				Engine->moduleSceneManager->CreateGameObject();
			}
			ImGui::EndPopup();
		}

	}
	ImGui::End();
	ImGui::ShowDemoWindow();
}

void HierarchyPanel::IterateGameObjectsTree(const GameObject * parent, int deep) const {
	if (parent->children.size() == 0) {
		return;
	}
	for (auto & child : parent->children) {
		ImGui::Text(child->name.c_str());
		IterateGameObjectsTree(child.get(), ++deep);
	}
}

