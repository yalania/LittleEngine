#include "LittleEngine.h"

LittleEngine::LittleEngine()
{
	// Order matters: they will Init/start/update in this order
	modules.reserve(2);
	modules.push_back(moduleWindow = std::make_shared<ModuleWindow>());
	modules.push_back(moduleInput = std::make_shared<ModuleInput>());
	modules.push_back(moduleRenderer = std::make_shared<ModuleRender>());
}

LittleEngine::~LittleEngine()
{
	CleanUp();
}

bool LittleEngine::Init()
{
	bool result = true;

	for(auto &module : modules) {
		bool ret = module->Init();
		if (!ret) {
			result = ret;
		}
	}

	return result;
}

update_status LittleEngine::Update()
{
	update_status result = UPDATE_CONTINUE;

	for (auto &module : modules) {
		update_status ret = module->PreUpdate();
		if (ret == UPDATE_ERROR || ret == UPDATE_STOP) {
			result = ret;
		}
	}
	if (result == UPDATE_CONTINUE) {
		for (auto &module : modules) {
			update_status ret = module->Update();
			if (ret == UPDATE_ERROR || ret == UPDATE_STOP) {
				result = ret;
			}
		}
	}

	if (result == UPDATE_CONTINUE) {
		for (auto &module : modules) {
			update_status ret = module->PostUpdate();
			if (ret == UPDATE_ERROR || ret == UPDATE_STOP) {
				result = ret;
			}
		}
	}

	return result;
}

bool LittleEngine::CleanUp()
{
	bool result = true;

	for (auto &module : modules) {
		bool ret = module->CleanUp();
		if (!ret) {
			result = ret;
		}
	}

	return result;
}
