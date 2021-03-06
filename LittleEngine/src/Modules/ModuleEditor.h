#pragma once
#include "Module.h"
#include <Editor/UI.h>

class ModuleEditor : public Module {

public:
	ModuleEditor() = default;
	~ModuleEditor() = default;
	bool Init() override;
	bool CleanUp() override;
	UpdateStatus Update() override;
	UpdateStatus PreUpdate() override;
	UpdateStatus PostUpdate() override;
private:
	UI mGeneralUI;
};

