#include "ModuleSceneManager.h"
#include "LittleEngine.h"


UpdateStatus ModuleSceneManager::Update() {

	for ( auto & gameObject : gameObjectsOwnership  )
	{
		gameObject->Update();
	}
	return UpdateStatus::UPDATE_CONTINUE;
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

	std::unique_ptr<GameObject> newGameObject = std::make_unique<GameObject>(gameObjectEmptyName, parent);
	GameObject * newGameObjectPtr = newGameObject.get();
	gameObjectsOwnership.push_back(std::move(newGameObject));
	parent->children.push_back(newGameObjectPtr);
	return newGameObjectPtr;
}

void ModuleSceneManager::RemoveGameObject(GameObject * gameObjectToRemove) {
	auto it = std::remove_if(gameObjectsOwnership.begin(), gameObjectsOwnership.end(), [gameObjectToRemove](auto const & gameObject)
	{
		return gameObject.get() == gameObjectToRemove;
	});
	gameObjectsOwnership.erase(it);
}

GameObject * ModuleSceneManager::GetRoot() const {
	return root.get();
}