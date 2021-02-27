#ifndef _INSPECTOR_PANEL_
#define _INSPECTOR_PANEL_
#include "../GameObject.h"

#include <Components/Mesh.h>

class InspectorPanel {
public:
	InspectorPanel() = default;
	~InspectorPanel() = default;
	void ShowGameObjectInfo();
	void ShowComponentInfo(Component & component);

	void AddNewComponent();
	GameObject * gameObject = nullptr;
	std::vector<char> writable;
	void ShowMeshComponentInfo(Mesh & mesh);
};
#endif // !_INSPECTOR_PANEL_

