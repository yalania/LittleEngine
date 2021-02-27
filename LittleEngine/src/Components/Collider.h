#ifndef _MODEL_COMPONENT_
#define _MODEL_COMPONENT_

#include "Component.h"
#include <vector>
#include "Mesh.h"
class Collider {

public:
	Collider() = default;

	Collider(Collider && model) = default;
	Collider(const Collider & model) = default;

	Collider& operator = (Collider && model) = default;
	Collider& operator = (const Collider & model) = default;
	void Update();

	std::vector<std::shared_ptr<Texture>> GetTextureInfo();
	void ShowCheckerBoardTexture(bool enable);
	void ChangeTexture(std::shared_ptr<Texture> newTexture);
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

