#ifndef _MODEL_COMPONENT_
#define _MODEL_COMPONENT_

#include "Component.h"
#include <vector>
#include "Mesh.h"
class Model : public Component {

public:
	Model(std::vector<Mesh> entityMeshes);
	update_status Update() override;
	float sphereRadius = 0.0f;
private:
	glm::vec3 CalculateCenter();
	void CalculateSphere();

	std::vector<Mesh> meshes;
	glm::vec3 sphereCenter;
};
#endif // !_MODEL_COMPONENT_

