#ifndef _HIERARCHY_PANEL_
#define _HIERARCHY_PANEL_
#include "InspectorPanel.h"

class HierarchyPanel {

public:
	HierarchyPanel() = default;
	~HierarchyPanel() = default;
	void ShowHierarchyPanel() const;


private:
	void IterateGameObjectsTree(const GameObject * parent, int deep) const;
	InspectorPanel inspector;
};
#endif // !_HIERARCHY_PANEL_

