#ifndef _UI_
#define _UI_
#include "PropertiesUI.h"
#include "HierarchyPanel.h"
#include "../Globals.h"
class UI {

public:
	UpdateStatus ShowUI();
	UI() = default;
	~UI() = default;


private:
	void DrawConsoleWindow();
	void DrawAboutWindow(); 
	void UpdateState();
	void TimeControlButtons();
	//void GeometryPropertiesTab();
	
	PropertiesUI PropertiesUI;
	HierarchyPanel hierarchyPanel;

};

#endif // !_UI_

