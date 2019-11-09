#ifndef _ENTITY_
#define _ENTITY_
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include <memory.h>
class Entity {
public:
	Entity(std::unique_ptr<Mesh> mesh);
	~Entity() = default;

	update_status Update();

private:
	std::unique_ptr<Mesh> entityMesh;
	std::unique_ptr<Transform> entityTransform;

};
#endif // !_ENTITY_

