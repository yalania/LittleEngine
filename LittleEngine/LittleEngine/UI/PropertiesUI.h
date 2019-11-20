#ifndef _UI_PROPERTIES_
#define _UI_PROPERTIES_
class PropertiesUI {

public:
	PropertiesUI() = default;
	~PropertiesUI() = default;
	void DrawPropertiesWindow();
private:
	void CameraPropertiesTab();
	void WindowPropertiesTab();
	void SystemPropertiesTab();
	void InputPropertiesTab();
	void RenderPropertiesTab();
};
#endif // !_UI_PROPERTIES_

