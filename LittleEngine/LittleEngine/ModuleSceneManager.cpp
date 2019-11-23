#include "ModuleSceneManager.h"
#include "LittleEngine.h"

GameObject * ModuleSceneManager::CreateGameObject() {
	std::shared_ptr<GameObject> newGameObject = std::make_shared<GameObject>("Game Object");
	root->children.push_back(newGameObject);
	return newGameObject.get();
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