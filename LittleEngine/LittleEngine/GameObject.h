#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_
#include "Components/Transform.h"
#include "Components/Model.h"
#include <memory.h>


class GameObject {
public:
	GameObject();
	GameObject(Model gameObjectModel, unsigned int shaderProgram);
	~GameObject() = default;

	update_status Update();

	Transform transform;
	std::unique_ptr<Model> model;
private:
	unsigned int shaderProgram;

};
#endif // !_GAME_OBJECT_

