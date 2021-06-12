#include "MeshImporter.h"
#include "Filesystem/Path.h"
#include <assimp/DefaultLogger.hpp>
#include <assimp/postprocess.h>

MeshImporter::MeshImporter() : Importer(ResourceType::MESH)
{
}


std::vector<char> MeshImporter::ExtractData(const aiMesh& mesh) const {
	std::vector<char> data;

	// data to fill
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh.mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh.mVertices[i].x;
		vector.y = mesh.mVertices[i].y;
		vector.z = mesh.mVertices[i].z;
		vertex.Position = vector;
		// normals
		vector.x = mesh.mNormals[i].x;
		vector.y = mesh.mNormals[i].y;
		vector.z = mesh.mNormals[i].z;
		vertex.Normal = vector;
		// texture coordinates
		if (mesh.mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh.mTextureCoords[0][i].x;
			vec.y = mesh.mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh.mNumFaces; i++)
	{
		aiFace face = mesh.mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// return a mesh object created from the extracted mesh data
	return Binarize(vertices, indices);
}

std::vector<char> MeshImporter::Binarize(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)  const
{
	uint32_t numIndices = indices.size();
	uint32_t numVertices = vertices.size();
	uint32_t ranges[2] = { numIndices, numVertices };

	uint32_t size = sizeof(ranges) + sizeof(uint32_t) * numIndices + sizeof(Vertex) * numVertices + sizeof(uint32_t);

	std::vector<char> data(size); // Allocate

	char* cursor = &data.front();
	size_t bytes = sizeof(ranges); // First store ranges
	memcpy(cursor, ranges, bytes);

	cursor += bytes; // Store indices
	bytes = sizeof(uint32_t) * numIndices;
	memcpy(cursor, &indices.front(), bytes);

	cursor += bytes; // Store vertices
	bytes = sizeof(Vertex) * numVertices;
	memcpy(cursor, &vertices.front(), bytes);

	return data;
}
