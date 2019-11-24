#include "ModuleSceneManager.h"
#include "LittleEngine.h"


update_status ModuleSceneManager::Update() {
	glUseProgram(Engine->moduleShaderProgram->defaultProgram);
	for (auto & transform : transforms) {
		if (!gameIsPaused) {
			transform->Update();
		}
	}
	glUseProgram(0);
	return UPDATE_CONTINUE;
}
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
	transforms.push_back(&newGameObject->transform);
	return newGameObject.get();
}


GameObject * ModuleSceneManager::GetRoot() const {
	return root.get();
}