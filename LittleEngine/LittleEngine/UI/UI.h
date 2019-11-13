#ifndef _BOTTOM_TAB_
#define _BOTTOM_TAB_


class UI {

public:
	UI() = default;
	~UI() = default;
	static void ShowUI();

private:

	static void TabExample();
	static void DrawConsoleWindow();
	static void DrawAboutWindow(); 
	static void DrawPropertiesWindow();
	static void UpdateState();
	static void TimeControlButtons();
};

#endif // !_BOTTOM_TAB_

