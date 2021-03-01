#ifndef _LITTLE_ENGINE_
#define _LITTLE_ENGINE_

#include <Modules/ModuleRender.h>
#include <Modules/ModuleProgram.h>
#include <Modules/ModuleCamera.h>
#include <Modules/ModuleTexture.h>
#include <Modules/ModuleGrid.h>
#include <Modules/ModuleModelLoader.h>
#include <Modules/ModuleTimeController.h>
#include <Modules/ModuleSceneManager.h>

#include <vector>
#include <memory>
class ModuleWindow;
class ModuleFilesystem;
class ModuleInput;
class ModuleEditor;
class ModuleResources;
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
	std::unique_ptr<ModuleEditor> moduleEditor;
	std::unique_ptr<ModuleCamera> moduleCamera;
	std::unique_ptr<ModuleTexture> moduleTexture;
	std::unique_ptr<ModuleGrid> moduleGrid;
	std::unique_ptr<ModuleModelLoader> moduleModelLoader;
	std::unique_ptr<ModuleTimeController> moduleTimeController;
	std::unique_ptr<ModuleSceneManager> moduleSceneManager;
	std::unique_ptr<ModuleFilesystem> moduleFilesystem;
	std::unique_ptr<ModuleResources> moduleResources;
private:

	std::vector<Module *> modules;

};

extern LittleEngine * Engine;


#endif // !_LITTLE_ENGINE_

