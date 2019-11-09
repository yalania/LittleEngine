#include "Entity.h"

Entity::Entity(std::unique_ptr<Mesh> mesh) : entityMesh(std::move(mesh)){
	entityTransform = std::make_unique<Transform>();
}


update_status Entity::Update(){
	update_status result = UPDATE_CONTINUE;
	result = entityTransform->Update();
	if (result == UPDATE_CONTINUE) {
		result = entityMesh->Update();
	}	
	return result;

}