#ifndef _ENTITY_
#define _ENTITY_
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include <memory.h>


class Entity {
public:
	Entity(std::vector<Mesh> entityMeshes, unsigned int shaderProgram);
	~Entity() = default;

	update_status Update();

	std::unique_ptr<Transform> entityTransform;
private:
	std::vector<Mesh> entityMeshes;
	unsigned int shaderProgram;

};
#endif // !_ENTITY_

