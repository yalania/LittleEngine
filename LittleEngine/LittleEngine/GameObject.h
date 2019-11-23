#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_
#include "Components/Transform.h"
#include "Components/Component.h"
#include <memory>
#include <vector>

class GameObject {
public:
	GameObject() = default;
	GameObject(const char * name );
	~GameObject() = default;

	void Update();

	Transform transform;
	std::vector<std::shared_ptr<Component>> components;
	std::string name = "";

	std::shared_ptr<GameObject> parent = nullptr;
	std::vector<std::shared_ptr<GameObject>> children;
private:
	unsigned int shaderProgram = 0;

};
#endif // !_GAME_OBJECT_

