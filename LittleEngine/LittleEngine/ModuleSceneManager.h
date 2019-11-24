#ifndef _MODULE_SCENE_MANAGER_
#define _MODULE_SCENE_MANAGER_
#include "Module.h"
#include <memory>
#include <vector>
#include "GameObject.h"
class ModuleSceneManager : public Module {

public:
	update_status Update() override;
	GameObject * GetRoot() const;
	GameObject * CreateGameObject();
	GameObject * CreateGameObjectChild(GameObject * parent);

	std::unique_ptr<GameObject> root = std::make_unique<GameObject>("Root");
	std::vector<Transform *> transforms;
};

#endif // !_MODULE_SCENE_MANAGER_

