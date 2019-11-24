#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_
#include "Components/Transform.h"
#include "Components/Component.h"
#include <vector>

class GameObject {
public:
	GameObject(const char * name, GameObject* parent);
	GameObject(std::string name, GameObject* parent);
	~GameObject() = default;

	void Update();
	std::vector<Component *> GetComponents(ComponentType type);
	void SetParent(GameObject * parent);
	void RemoveChildren(GameObject * gameObject);

	Transform transform;
	std::vector<Component *> components;
	std::string name = "";

	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	bool active = true;
	bool staticGameObject = false;

};
#endif // !_GAME_OBJECT_

