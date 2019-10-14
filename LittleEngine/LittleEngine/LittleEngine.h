#ifndef _LLITTLE_ENGINE_
#define _LLITTLE_ENGINE_

#include <vector>
#include <memory>
#include "ModuleWindow.h"

class LittleEngine {

public:

	LittleEngine();
	~LittleEngine();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	//std::unique_ptr<ModuleRender> renderer;
	std::shared_ptr<ModuleWindow> window;
	//std::unique_ptr<ModuleInput> input;

private:

	std::vector<std::shared_ptr<Module>> modules;

};




#endif // !_LLITTLE_ENGINE_

