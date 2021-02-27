#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_
#include <Components/Transform.h>
#include <Components/Component.h>
#include <vector>

class GameObject {
public:
	GameObject(const char * name, GameObject* parent);
	GameObject(std::string name, GameObject* parent);
	~GameObject();

	void Update();
	std::vector<Component *> GetComponents(ComponentType type);
	void SetParent(GameObject * parent);
	void RemoveChild(GameObject * gameObject);
	void AddChild(GameObject * gameObject);
	void Delete();

	Transform transform;
	std::vector<Component *> components;
	std::vector<GameObject*> children;
	GameObject* parent = nullptr;
	std::string name = "";

	bool active = true;
	bool staticGameObject = false;

};
#endif // !_GAME_OBJECT_

