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
	glm::vec3 sphereCenter;
private:
	glm::vec3 CalculateCenter();
	void CalculateSphere();
	void CalculateAxisAlignBoudingBox();

	std::vector<Mesh> meshes;
	Mesh boundingBox;
};
#endif // !_MODEL_COMPONENT_

