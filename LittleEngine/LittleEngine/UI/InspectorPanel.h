#ifndef _INSPECTOR_PANEL_
#define _INSPECTOR_PANEL_
#include "../GameObject.h"

class InspectorPanel {
public:
	InspectorPanel() = default;
	~InspectorPanel() = default;
	void ShowGameObjectInfo();
	void ShowComponentInfo(Component & component);
	void AddNewComponent();
	GameObject * gameObject = nullptr;
	std::vector<char> writable;
};
#endif // !_INSPECTOR_PANEL_

