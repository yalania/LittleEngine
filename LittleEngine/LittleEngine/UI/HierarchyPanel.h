#ifndef _HIERARCHY_PANEL_
#define _HIERARCHY_PANEL_
#include "InspectorPanel.h"
#include "../imgui/imgui.h"
class HierarchyPanel {

public:
	HierarchyPanel() = default;
	~HierarchyPanel() = default;
	void ShowHierarchyPanel();
	void PopupOnClickPanel();
	void CheckDragAndDrop(GameObject * gameObject);

private:
	void IterateGameObjectsTree(const GameObject * parent, int deep);
	InspectorPanel inspector;

	//Dragging
	ImVec2 dropPossition;
	bool dragging = false;



};
#endif // !_HIERARCHY_PANEL_

