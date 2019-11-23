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
#include "ModuleModelLoader.h"
#include "ModuleTimeController.h"
#include "ModuleSceneManager.h"

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
	std::unique_ptr<ModuleRender> moduleRenderer;
	std::unique_ptr<ModuleWindow> moduleWindow;
	std::unique_ptr<ModuleInput> moduleInput;
	std::unique_ptr<ModuleProgram> moduleShaderProgram;
	std::unique_ptr<ModuleIMGUI> moduleImgui;
	std::unique_ptr<ModuleCamera> moduleCamera;
	std::unique_ptr<ModuleTexture> moduleTexture;
	std::unique_ptr<ModuleGrid> moduleGrid;
	std::unique_ptr<ModuleModelLoader> moduleModelLoader;
	std::unique_ptr<ModuleTimeController> moduleTimeController;
	std::unique_ptr<ModuleSceneManager> moduleSceneManager;

private:

	std::vector<Module *> modules;

};

extern LittleEngine * Engine;


#endif // !_LITTLE_ENGINE_

