#ifndef _INSPECTOR_PANEL_
#define _INSPECTOR_PANEL_
#include "../GameObject.h"

class InspectorPanel {
public:
	InspectorPanel() = default;
	~InspectorPanel() = default;
	void ShowGameObjectInfo(GameObject & gameObject) const;
};
#endif // !_INSPECTOR_PANEL_

