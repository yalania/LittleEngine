#ifndef _MODULE_SCENE_MANAGER_
#define _MODULE_SCENE_MANAGER_
#include "Module.h"
#include <memory>
#include <vector>
#include "GameObject.h"
class ModuleSceneManager : public Module {

public:
	const GameObject * GetRoot() const;
	void CreateGameObject();
	void ProcessFile(const char * file);

	std::unique_ptr<GameObject> root = std::unique_ptr<GameObject>();
};

#endif // !_MODULE_SCENE_MANAGER_

