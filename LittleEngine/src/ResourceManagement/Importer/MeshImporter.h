#pragma once
#include "Importer.h"
#include <string>
#include <assimp/scene.h>
#include <Components/Mesh.h>
#include "Log.h"
#include <assimp/Importer.hpp>

class MeshImporter : public Importer {
public:
	MeshImporter();
	~MeshImporter() = default;
	std::vector<char> ExtractData(const aiMesh& mesh) const;
	std::vector<char> Binarize(const std::vector<Vertex> & vertices,const std::vector<uint32_t> & indices) const;
};

