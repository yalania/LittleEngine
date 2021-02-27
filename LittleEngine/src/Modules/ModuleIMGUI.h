#ifndef _MODULE_IMGUI_
#define _MODULE_IMGUI_
#include "Module.h"
#include <Editor/UI.h>

class ModuleIMGUI : public Module {

public:
	ModuleIMGUI() = default;
	~ModuleIMGUI() = default;
	bool Init() override;
	bool CleanUp() override;
	update_status Update() override;
	update_status PreUpdate() override;
	update_status PostUpdate() override;
private:
	UI generalUi;
};
#endif // _MODULE_IMGUI_

