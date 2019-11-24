#include "HierarchyPanel.h"

#include "../LittleEngine.h"

ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_OpenOnArrow;

void HierarchyPanel::ShowHierarchyPanel() {
	ImGui::Begin("Hierarchy Panel");
	static GameObject * sceneRoot = Engine->moduleSceneManager->GetRoot();
	if (ImGui::TreeNodeEx(sceneRoot->name.c_str(), treeFlags | ImGuiTreeNodeFlags_DefaultOpen)) {
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
				inspector.gameObject = child;
			}
			CheckDragAndDrop(child);
		}else {
			if (ImGui::TreeNodeEx(child->name.c_str(), treeFlags)) {
				if ((ImGui::IsItemHovered() || ImGui::IsItemFocused()) && ImGui::GetIO().MouseClicked[0]) {
					inspector.gameObject = child;
				}
				ImGui::TreePop();
			}
			IterateGameObjectsTree(child, ++deep);
		}
	}
}


void HierarchyPanel::PopupOnClickPanel() {

	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::Selectable("Create empty")) {
			if (inspector.gameObject == nullptr) {
				Engine->moduleSceneManager->CreateGameObject();
			}
			else {
				Engine->moduleSceneManager->CreateGameObjectChild(inspector.gameObject);
			}
		}
		ImGui::EndPopup();
	}

	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup)) {
		inspector.gameObject = nullptr;
	}
}

void HierarchyPanel::CheckDragAndDrop(GameObject * gameObject) {

	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
		ImGui::SetDragDropPayload("DRAG", gameObject,sizeof(GameObject));
		ImGui::EndDragDropSource();
	}
	if (ImGui::BeginDragDropTarget()) {
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG");
		if (payload != nullptr) {
			assert(payload->DataSize == sizeof(GameObject));
			GameObject * newChild = reinterpret_cast<GameObject*>(payload->Data);
			newChild->SetParent(gameObject);
		}
		ImGui::EndDragDropTarget();
	}
	
}