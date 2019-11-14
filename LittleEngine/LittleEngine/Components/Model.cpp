#include "Model.h"


Model::Model(std::vector<Mesh> meshes) : meshes(meshes){
	CalculateSphere();
}
update_status Model::Update() {
	update_status result = UPDATE_CONTINUE;
	for (auto &mesh : meshes) {
		mesh.Update();
	}
	return result;
}

void Model::CalculateSphere() {
	sphereCenter = CalculateCenter();
	for (auto & mesh : meshes) {
		for (auto & vector : mesh.vertices) {
			float distanceFromCenter = (vector.Position - sphereCenter).length();
			if (distanceFromCenter > sphereRadius) {
				sphereRadius = distanceFromCenter;
			}
		}
	}
}

glm::vec3 Model::CalculateCenter() {
	glm::vec3 vectorAddition = glm::vec3(0.0f);
	float totalVectorSize = 0.0f;
	for (auto & mesh : meshes) {
		for (auto & vector : mesh.vertices) {
			vectorAddition += vector.Position;
		}
		totalVectorSize+=mesh.vertices.size();
	}
	return vectorAddition / totalVectorSize;
}