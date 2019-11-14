#ifndef _MESH_COMPONENT_
#define _MESH_COMPONENT_
#include "Component.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh : public Component {

public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	Mesh(Mesh && mesh) = default;
	Mesh(const Mesh & mesh) = default;

	Mesh& operator = (Mesh && mesh) = default;
	Mesh& operator = (const Mesh & mesh) = default;

	update_status Update() override;

private:
	void setupMesh();
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	
	unsigned int VBO = 0;
	unsigned int EBO = 0;
	unsigned int VAO = 0;

 };

#endif // !_MESH_COMPONENT_

