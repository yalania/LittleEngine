#pragma once
#include "Module.h"
#include <Editor/UI.h>

class ModuleEditor : public Module {

public:
	ModuleEditor() = default;
	~ModuleEditor() = default;
	bool Init() override;
	bool CleanUp() override;
	update_status Update() override;
	update_status PreUpdate() override;
	update_status PostUpdate() override;
private:
	UI mGeneralUI;
};

