#include "ModuleSceneManager.h"
#include "LittleEngine.h"

void ModuleSceneManager::CreateGameObject() {
	root->children.push_back(std::make_shared<GameObject>("Game Object"));
}

void ModuleSceneManager::ProcessFile(const char * file) {
	/*std::string fileExtension = std::string(file).substr(std::string(file).find_last_of('.'), -1);
	std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
	if (fileExtension == ".fbx") {
		AddGameObject(file);
		Engine->moduleCamera->FocusOnGameObject(GetGameObject());
	}
	else {
		GetGameObject().model->ChangeTexture(Engine->moduleTexture->LoadTexture(file));

	}*/
}

const GameObject * ModuleSceneManager::GetRoot() const {
	return root.get();
}