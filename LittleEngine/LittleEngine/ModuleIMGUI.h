#ifndef _MODULE_IMGUI_
#define _MODULE_IMGUI_
#include "Module.h"

class ModuleIMGUI : public Module {

public:
	bool Init() override;
	bool CleanUp() override;
	update_status Update() override;
	update_status PreUpdate() override;
	update_status PostUpdate() override;

private:


};
#endif // _MODULE_IMGUI_

