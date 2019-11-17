#ifndef _ENTITY_
#define _ENTITY_
#include "Components/Transform.h"
#include "Components/Model.h"
#include <memory.h>


class Entity {
public:
	Entity();
	Entity(Model entityModel, unsigned int shaderProgram);
	~Entity() = default;

	update_status Update();

	std::unique_ptr<Transform> entityTransform;
	std::unique_ptr<Model> entityModel;
private:
	unsigned int shaderProgram;

};
#endif // !_ENTITY_

