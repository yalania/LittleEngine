#pragma once
#include "Importer.h"
#include <string>
#include <memory>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
class MeshImporter;
class Metafile;
class Texture;
class ModelImporter : public Importer {
public:
	ModelImporter();
	~ModelImporter();
	std::vector<char> ExtractData(const std::unique_ptr<Path>& assetsFilePath, const Metafile& metafile) const override;
private:
	void ProcessNode(const aiNode &node, const aiScene &scene) const;
	void SaveResource(const std::vector<char>& data, std::unique_ptr<Metafile>& nodeMetafile) const;
	void ProcessMaterial(std::vector<std::shared_ptr<Texture>> &textures, const aiMesh &mesh, const aiScene &scene) const;

	std::unique_ptr<Assimp::Importer> import = std::make_unique<Assimp::Importer>();
	std::unique_ptr<MeshImporter> mMeshImporter;

	struct CurrentModelData
	{
		float mScale = 1.f;
		Metafile* mModelMetafile;
		std::vector<std::unique_ptr<Metafile>> mNodesMetafile;
	};
	mutable CurrentModelData mCurrentModelData;
};

