#include "HierarchyPanel.h"
#include "../imgui/imgui.h"
#include "../LittleEngine.h"

void HierarchyPanel::ShowHierarchyPanel() {
	ImGui::Begin("Hierarchy Panel");
	static GameObject * sceneRoot = Engine->moduleSceneManager->GetRoot();
	if (ImGui::TreeNode(sceneRoot->name.c_str())) {
		if ((ImGui::IsItemHovered() || ImGui::IsItemFocused()) && ImGui::GetIO().MouseClicked[0]) {
			inspector.gameObject = sceneRoot;
		}
		IterateGameObjectsTree(sceneRoot, 0);
		ImGui::TreePop();
	}
	PopupOnClickPanel();
	
	ImGui::End();
	inspector.ShowGameObjectInfo();
	ImGui::ShowDemoWindow();
}

void HierarchyPanel::IterateGameObjectsTree(const GameObject * parent, int deep) {
	for (auto & child : parent->children) {
		if (child->children.size() == 0) {
			ImGui::Selectable(child->name.c_str());
			if ((ImGui::IsItemHovered() || ImGui::IsItemFocused()) && ImGui::GetIO().MouseClicked[0]) {
				inspector.gameObject = child.get();
			}

		}else if (ImGui::TreeNode(child->name.c_str())) {
			IterateGameObjectsTree(child.get(), ++deep);
			ImGui::TreePop();
		}
	}
}


void HierarchyPanel::PopupOnClickPanel() {

	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::Selectable("Create empty")) {
			Engine->moduleSceneManager->CreateGameObject();
		}
		ImGui::EndPopup();
	}
}