#ifndef _MODEL_COMPONENT_
#define _MODEL_COMPONENT_

#include "Component.h"
#include <vector>
#include "Mesh.h"
class Model : public Component {

public:
	Model() = default;
	Model(std::vector<Mesh> entityMeshes);
	update_status Update() override;

	std::vector<std::shared_ptr<Texture>> GetTextureInfo();
	void ShowCheckerBoardTexture(bool enable);
	void ChangeTexture(const Texture & newTexture);
private:
	glm::vec3 CalculateCenter();
	void CalculateSphere();
	void CalculateAxisAlignBoudingBox();

private:
	Mesh boundingBox;

public:
	float sphereRadius = 0.0f;
	glm::vec3 sphereCenter = glm::vec3(0.0f);
	std::vector<Mesh> meshes;
	bool activateBoudingBox = false;
	int totalVertexCount = 0;
	int totalTriangleCount = 0;
};
#endif // !_MODEL_COMPONENT_

