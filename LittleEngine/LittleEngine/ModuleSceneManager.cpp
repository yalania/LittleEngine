#include "ModuleSceneManager.h"
#include "LittleEngine.h"

GameObject * ModuleSceneManager::CreateGameObject() {
	return CreateGameObjectChild(root.get());
}

GameObject * ModuleSceneManager::CreateGameObjectChild(GameObject * parent) {
	int numberOfGameObjectWithSameName = 0;
	std::string gameObjectEmptyName("Game Object");
	for (auto & child : parent->children)
	{
		if (child->name.find(gameObjectEmptyName) != std::string::npos) {
				++numberOfGameObjectWithSameName;
		}
	}
	if (numberOfGameObjectWithSameName != 0) {
		gameObjectEmptyName += " (" + std::to_string(numberOfGameObjectWithSameName) + ")";
	}

	std::shared_ptr<GameObject> newGameObject = std::make_shared<GameObject>(gameObjectEmptyName);
	parent->children.push_back(newGameObject);
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

GameObject * ModuleSceneManager::GetRoot() const {
	return root.get();
}