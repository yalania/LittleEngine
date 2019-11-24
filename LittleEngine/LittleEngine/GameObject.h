#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_
#include "Components/Transform.h"
#include "Components/Component.h"
#include <vector>

class GameObject : std::enable_shared_from_this<GameObject> {
public:
	GameObject(const char * name, std::shared_ptr<GameObject> parent);
	GameObject(std::string name, std::shared_ptr<GameObject> parent);
	~GameObject() = default;

	void Update();
	std::vector<Component *> GetComponents(ComponentType type);
	void SetParent(GameObject * parent);
	void RemoveChildren(GameObject * gameObject);

	Transform transform;
	std::vector<Component *> components;
	std::string name = "";

	std::shared_ptr<GameObject> parent = nullptr;
	std::vector<std::shared_ptr<GameObject>> children;
	bool active = true;
	bool staticGameObject = false;

};
#endif // !_GAME_OBJECT_

