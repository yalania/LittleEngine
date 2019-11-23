#ifndef _INSPECTOR_PANEL_
#define _INSPECTOR_PANEL_
#include "../GameObject.h"

class InspectorPanel {
public:
	InspectorPanel() = default;
	~InspectorPanel() = default;
	void ShowGameObjectInfo() const;
	void ShowComponentInfo(Component & component);
	void AddNewComponent();
	GameObject * gameObject = nullptr;
};
#endif // !_INSPECTOR_PANEL_

