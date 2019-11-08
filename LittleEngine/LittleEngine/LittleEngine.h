#ifndef _LITTLE_ENGINE_
#define _LITTLE_ENGINE_

#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleProgram.h"
#include "ModuleIMGUI.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "ModuleGrid.h"

#include <vector>
#include <memory>

class LittleEngine {

public:

	LittleEngine();
	virtual ~LittleEngine();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	std::shared_ptr<ModuleRender> moduleRenderer;
	std::shared_ptr<ModuleWindow> moduleWindow;
	std::shared_ptr<ModuleInput> moduleInput;
	std::shared_ptr<ModuleProgram> moduleShaderProgram;
	std::shared_ptr<ModuleIMGUI> moduleImgui;
	std::shared_ptr<ModuleCamera> moduleCamera;
	std::shared_ptr<ModuleTexture> moduleTexture;
	std::shared_ptr<ModuleGrid> moduleGrid;

private:

	std::vector<std::shared_ptr<Module>> modules;

};

extern LittleEngine * Engine;


#endif // !_LITTLE_ENGINE_

