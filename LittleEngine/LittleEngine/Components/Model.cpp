#include "Model.h"


Model::Model(std::vector<Mesh> entityMeshes) : entityMeshes(entityMeshes){

}
update_status Model::Update() {
	update_status result = UPDATE_CONTINUE;
	for (auto &mesh : entityMeshes) {
		mesh.Update();
	}
	return result;
}