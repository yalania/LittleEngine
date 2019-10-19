#ifndef _LLITTLE_ENGINE_
#define _LLITTLE_ENGINE_

#include <vector>
#include <memory>
#include "ModuleRender.h"
#include "ModuleWindow.h"

class LittleEngine {

public:

	LittleEngine();
	~LittleEngine();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	std::shared_ptr<ModuleRender> moduleRenderer = nullptr;
	std::shared_ptr<ModuleWindow> moduleWindow = nullptr;
	int x;
	//std::unique_ptr<ModuleInput> input;

private:

	std::vector<std::shared_ptr<Module>> modules;

};

extern LittleEngine * Engine;


#endif // !_LLITTLE_ENGINE_

