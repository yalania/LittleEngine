#include "Collider.h"
#include <gl/GL.h>
#include <algorithm>

void Collider::Update() {
	UpdateStatus result = UpdateStatus::UPDATE_CONTINUE;

	for (auto &mesh : meshes) {
		mesh.Update();
	}
	if (activateBoudingBox) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		boundingBox.Update();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	};
}

void Collider::CalculateSphere() {
	sphereCenter = CalculateCenter();
	for (auto & mesh : meshes) {
		for (auto & vector : mesh.vertices) {
			float distanceFromCenter = glm::length(vector.Position - sphereCenter);
			if (distanceFromCenter > sphereRadius) {
				sphereRadius = distanceFromCenter;
			}
		}
	}
}

glm::vec3 Collider::CalculateCenter() {
	glm::vec3 vectorAddition = glm::vec3(0.0f);
	totalVertexCount = 0;
	totalTriangleCount = 0;
	for (auto & mesh : meshes) {
		for (auto & vector : mesh.vertices) {
			vectorAddition += vector.Position;
		}
		totalVertexCount +=mesh.vertices.size();
		totalTriangleCount += mesh.meshInfo.numberOfTriangles;
	}
	return vectorAddition / static_cast<float>(totalVertexCount);
}

void Collider::CalculateAxisAlignBoudingBox(){
	glm::vec3 firstMeshVertexPosition = meshes.at(0).vertices.at(0).Position;
	float maxX = firstMeshVertexPosition.x;
	float maxY = firstMeshVertexPosition.y;
	float maxZ = firstMeshVertexPosition.z;

	float minX = maxX;
	float minY = maxY;
	float minZ = maxZ;

	for (auto & mesh : meshes) {
		for (auto & vector : mesh.vertices) {
			
			maxX = vector.Position.x > maxX ? vector.Position.x : maxX;
			maxY = vector.Position.y > maxY ? vector.Position.y : maxY;
			maxZ = vector.Position.z > maxZ ? vector.Position.z : maxZ;

			minX = vector.Position.x < minX ? vector.Position.x : minX;
			minY = vector.Position.y < minY ? vector.Position.y : minY;
			minZ = vector.Position.z < minZ ? vector.Position.z : minZ;

			}
	}
	std::vector<Vertex> axisAlignBoudingBox;
	axisAlignBoudingBox.push_back({glm::vec3(maxX, maxY, maxZ)}); // 0
	axisAlignBoudingBox.push_back({glm::vec3(minX, maxY, maxZ)}); // 1
	axisAlignBoudingBox.push_back({glm::vec3(minX, minY, maxZ)}); // 2
	axisAlignBoudingBox.push_back({glm::vec3(maxX, minY, maxZ)}); // 3
	axisAlignBoudingBox.push_back({glm::vec3(maxX, maxY, minZ)}); // 4
	axisAlignBoudingBox.push_back({glm::vec3(maxX, minY, minZ)}); // 5
	axisAlignBoudingBox.push_back({glm::vec3(minX, minY, minZ)}); // 6
	axisAlignBoudingBox.push_back({glm::vec3(minX, maxY, minZ)}); // 7

	std::vector<unsigned int> axisAlignBoudingBoxIndex = {
		0,1,2,
		3,0,2,
		3,5,4,
		4,0,3,
		4,5,7,
		5,6,7,
		6,1,7,
		6,2,1,
		0,7,1,
		0,4,7,
		6,3,2,
		6,5,3
	};

	boundingBox = Mesh(axisAlignBoudingBox, axisAlignBoudingBoxIndex, {});
}


std::vector<std::shared_ptr<Texture>> Collider::GetTextureInfo() {
	std::vector<std::shared_ptr<Texture>> textureInfo;

	for (auto & mesh : meshes) {
		for (auto & texture : mesh.textures) {
			auto it = find_if(textureInfo.begin(), textureInfo.end(), [texture](std::shared_ptr<Texture> vectorTexture) { return vectorTexture->path == texture->path; });
			if (it == textureInfo.end()) {
				textureInfo.push_back(texture);
			}
		}
	}

	return textureInfo;
}

void Collider::ShowCheckerBoardTexture(bool enable) {
	for (auto & mesh : meshes) {
		mesh.showCheckerboardTexture = enable;
	}
}


void Collider::ChangeTexture(std::shared_ptr<Texture> newTexture) {
	for (auto & mesh : meshes) {
		for (auto & texture : mesh.textures) {
			texture = newTexture;
		}
	}
}