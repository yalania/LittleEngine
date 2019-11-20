#ifndef _BOTTOM_TAB_
#define _BOTTOM_TAB_
#include "../LittleEngine.h"
#include "../imgui/imgui.h"

class UI {

public:
	static update_status ShowUI();

private:
	UI() = default;
	~UI() = default;

	static void TabExample();
	static void DrawConsoleWindow();
	static void DrawAboutWindow(); 
	static void DrawPropertiesWindow();
	static void UpdateState();
	static void TimeControlButtons();
	static void CameraPropertiesTab();
	static void WindowPropertiesTab();
	static void SystemPropertiesTab();
	static void GeometryPropertiesTab();
	static void InputPropertiesTab();
	static void RenderPropertiesTab();
};

#endif // !_BOTTOM_TAB_

