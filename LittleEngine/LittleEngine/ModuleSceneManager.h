#ifndef _MODULE_SCENE_MANAGER_
#define _MODULE_SCENE_MANAGER_
#include "Module.h"
#include <memory>
#include <vector>
#include "GameObject.h"
class ModuleSceneManager : public Module {

public:
	GameObject& GetGameObject() const;
	void AddGameObject(const char * model);
	void ProcessFile(const char * file);


	std::unique_ptr<GameObject> missingGameObject = std::make_unique<GameObject>();
	std::vector<std::unique_ptr<GameObject>> gameObjects;
};

#endif // !_MODULE_SCENE_MANAGER_

