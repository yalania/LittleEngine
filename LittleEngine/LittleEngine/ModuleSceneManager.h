#ifndef _MODULE_SCENE_MANAGER_
#define _MODULE_SCENE_MANAGER_
#include "Module.h"
#include <memory>
#include <vector>
#include "GameObject.h"
class ModuleSceneManager : public Module {

public:
	GameObject * GetRoot() const;
	GameObject * CreateGameObject();
	GameObject * CreateGameObjectChild(GameObject * parent);

	std::unique_ptr<GameObject> root = std::make_unique<GameObject>("Root", nullptr);
	std::vector<std::unique_ptr<GameObject>> gameObjectsOwnership;
};

#endif // !_MODULE_SCENE_MANAGER_

