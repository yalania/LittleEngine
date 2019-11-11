#include "LittleEngine.h"

LittleEngine::LittleEngine()
{
	// Order matters: they will Init/start/update in this order
	modules.reserve(6);
	modules.push_back(moduleWindow = std::make_shared<ModuleWindow>());
	modules.push_back(moduleInput = std::make_shared<ModuleInput>());
	modules.push_back(moduleImgui = std::make_shared<ModuleIMGUI>());
	modules.push_back(moduleModelLoader = std::make_shared<ModuleModelLoader>());
	modules.push_back(moduleRenderer = std::make_shared<ModuleRender>());
	modules.push_back(moduleShaderProgram = std::make_shared<ModuleProgram>());
	modules.push_back(moduleCamera = std::make_shared<ModuleCamera>());
	modules.push_back(moduleTexture = std::make_shared<ModuleTexture>());
	modules.push_back(moduleGrid = std::make_shared<ModuleGrid>());
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
	//moduleRenderer->AddEntity("BakerHouse.fbx"); //TODO: THIS IS FOR DEBUGGING
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
