#include "ModuleSceneManager.h"
#include "LittleEngine.h"

void ModuleSceneManager::AddGameObject(const char * model) {
	Model newModel = Engine->moduleModelLoader->LoadModel(model);
	gameObjects.erase(gameObjects.begin(), gameObjects.end()); //ASSIMENT: For now because the assiment requirements
	gameObjects.push_back(std::make_unique<GameObject>(newModel, Engine->moduleShaderProgram->defaultProgram));
	Engine->moduleCamera->FocusOnGameObject(*gameObjects.back());
}

void ModuleSceneManager::ProcessFile(const char * file) {
	std::string fileExtension = std::string(file).substr(std::string(file).find_last_of('.'), -1);
	std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
	if (fileExtension == ".fbx") {
		AddGameObject(file);
		Engine->moduleCamera->FocusOnGameObject(GetGameObject());
	}
	else {
		GetGameObject().model->ChangeTexture(Engine->moduleTexture->LoadTexture(file));

	}
}

GameObject& ModuleSceneManager::GetGameObject() const {
	if (gameObjects.size() > 0) {
		return *gameObjects.front();
	}
	else {
		return *missingGameObject.get();
	}
}