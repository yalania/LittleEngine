#include "LittleEngine.h"
#include "Log.h"

#include <Modules/ModuleWindow.h>
#include <Modules/ModuleInput.h>
#include <Modules/ModuleFilesystem.h>
#include <Modules/ModuleEditor.h>
#include <Modules/ModuleResources.h>
LittleEngine::LittleEngine()
{
	// Order matters: they will Init/start/update in this order

	modules.reserve(15);
	modules.push_back((moduleFilesystem = std::make_unique<ModuleFilesystem>()).get());
	modules.push_back((moduleResources = std::make_unique<ModuleResources>()).get());
	modules.push_back((moduleSceneManager = std::make_unique<ModuleSceneManager>()).get());
	modules.push_back((moduleWindow = std::make_unique<ModuleWindow>()).get());
	modules.push_back((moduleTimeController = std::make_unique<ModuleTimeController>()).get());
	modules.push_back((moduleInput = std::make_unique<ModuleInput>()).get());
	modules.push_back((moduleModelLoader = std::make_unique<ModuleModelLoader>()).get());
	modules.push_back((moduleEditor = std::make_unique<ModuleEditor>()).get());
	modules.push_back((moduleRenderer = std::make_unique<ModuleRender>()).get());
	modules.push_back((moduleShaderProgram = std::make_unique<ModuleProgram>()).get());
	modules.push_back((moduleCamera = std::make_unique<ModuleCamera>()).get());
	modules.push_back((moduleTexture = std::make_unique<ModuleTexture>()).get());
	modules.push_back((moduleGrid = std::make_unique<ModuleGrid>()).get());
}

LittleEngine::~LittleEngine()
{
	CleanUp();
	_CrtDumpMemoryLeaks();
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
	LOG("Time for init Engine %f milliseconds", moduleTimeController->realTimeClock.Read());
	return result;
}

UpdateStatus LittleEngine::Update()
{
	UpdateStatus result = UpdateStatus::UPDATE_CONTINUE;
	for (auto &module : modules) {
		UpdateStatus ret = module->PreUpdate();
		if (ret == UpdateStatus::UPDATE_ERROR || ret == UpdateStatus::UPDATE_STOP) {
			result = ret;
		}
	}
	if (result == UpdateStatus::UPDATE_CONTINUE) {
		for (auto &module : modules) {
			UpdateStatus ret = module->Update();
			if (ret == UpdateStatus::UPDATE_ERROR || ret == UpdateStatus::UPDATE_STOP) {
				result = ret;
			}
		}
	}

	if (result == UpdateStatus::UPDATE_CONTINUE) {
		for (auto &module : modules) {
			UpdateStatus ret = module->PostUpdate();
			if (ret == UpdateStatus::UPDATE_ERROR || ret == UpdateStatus::UPDATE_STOP) {
				result = ret;
			}
		}
	}
	moduleTimeController->LimitFrameRate();
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
