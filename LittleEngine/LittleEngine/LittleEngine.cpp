#include "LittleEngine.h"

using namespace std;

LittleEngine::LittleEngine()
{
	// Order matters: they will Init/start/update in this order
	modules.reserve(1);
	modules.push_back(moduleRenderer = std::make_shared<ModuleRender>());
	modules.push_back(moduleWindow = std::make_shared<ModuleWindow>());
}

LittleEngine::~LittleEngine()
{
	CleanUp();
}

bool LittleEngine::Init()
{
	bool ret = true;

	for(auto moduleIt = modules.begin(); moduleIt != modules.end(); ++moduleIt) {
		ret = (*moduleIt)->Init();
	}

	return ret;
}

update_status LittleEngine::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (auto moduleIt = modules.begin(); moduleIt != modules.end(); ++moduleIt) {
		ret = (*moduleIt)->PreUpdate();
	}
	for (auto moduleIt = modules.begin(); moduleIt != modules.end(); ++moduleIt) {
		ret = (*moduleIt)->Update();
	}
	for (auto moduleIt = modules.begin(); moduleIt != modules.end(); ++moduleIt) {
		ret = (*moduleIt)->PostUpdate();
	}

	return ret;
}

bool LittleEngine::CleanUp()
{
	bool ret = true;

	for (auto moduleIt = modules.begin(); moduleIt != modules.end(); ++moduleIt) {
		ret = (*moduleIt)->CleanUp();
	}

	return ret;
}
