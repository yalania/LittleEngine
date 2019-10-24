#ifndef _LITTLE_ENGINE_
#define _LITTLE_ENGINE_

#include <vector>
#include <memory>
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleProgram.h"

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

private:

	std::vector<std::shared_ptr<Module>> modules;

};

extern LittleEngine * Engine;


#endif // !_LITTLE_ENGINE_

