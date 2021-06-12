#include "ModelImporter.h"
#include "Filesystem/Path.h"
#include <assimp/DefaultLogger.hpp>
#include <assimp/postprocess.h>

#include "Log.h"
#include "MeshImporter.h"
#include "ResourceManagement/Metafile/Metafile.h"
#include "ResourceManagement/Metafile/MetafileManager.h"
#include "LittleEngine.h"
#include "Modules/ModuleFilesystem.h"
ModelImporter::ModelImporter() : Importer(ResourceType::MODEL)
{
	static unsigned int flags = Assimp::Logger::VERBOSE | Assimp::Logger::Err | Assimp::Logger::Warn | Assimp::Logger::Debugging;
	Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
	Assimp::DefaultLogger::get()->attachStream(new AssimpLog(), flags);
}

ModelImporter::~ModelImporter()
{
	Assimp::DefaultLogger::kill();
}


std::vector<char> ModelImporter::ExtractData(const std::unique_ptr<Path>& assetsFilePath, const Metafile& metafile) const {
	mCurrentModelData.mModelMetafile = const_cast<Metafile*>(&metafile);
	std::vector<char> data;
	const aiScene *scene = import->ReadFile(assetsFilePath->GetFullPath(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG( "ERROR::ASSIMP::%s", import->GetErrorString());
		return data;
	}
	ProcessNode(*scene->mRootNode, *scene);
	return data;
}

void ModelImporter::ProcessNode(const aiNode &node, const aiScene &scene) const
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node.mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene.mMeshes[node.mMeshes[i]];
		if (mesh)
		{
			std::unique_ptr<Metafile> nodeMetafile = std::make_unique<Metafile>();
			nodeMetafile->mResourceType = ResourceType::MESH;
			nodeMetafile->mResourceName = std::string(node.mName.data) + ".mesh";			
			SaveResource(mMeshImporter->ExtractData(*mesh), nodeMetafile);
		}
	}
	// after we've processed all of the data (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node.mNumChildren; i++)
	{
		ProcessNode(*node.mChildren[i], scene); //Recursive!!
	}

}

void ModelImporter::SaveResource(const std::vector<char>& data, std::unique_ptr<Metafile>& nodeMetafile) const
{

	nodeMetafile->mMetafilePath = mCurrentModelData.mModelMetafile->mMetafilePath;
	nodeMetafile->mImportedFilePath = mCurrentModelData.mModelMetafile->mImportedFilePath;

	nodeMetafile->uuid = MetafileManager::GenerateUUID();
	nodeMetafile->mExportedFilePath = MetafileManager::GetUUIDExportedFolder(nodeMetafile->uuid);
	auto & metafileExportedPath = Engine->moduleFilesystem->FindOrCreatePath(nodeMetafile->mExportedFilePath);

	metafileExportedPath->GetFile()->Save(data);
	mCurrentModelData.mNodesMetafile.push_back(std::move(nodeMetafile));
}


void ModelImporter::ProcessMaterial(std::vector<std::shared_ptr<Texture>> &textures, const aiMesh &mesh, const aiScene &scene) const{
	
	// process materials
	aiMaterial* material = scene.mMaterials[mesh.mMaterialIndex];

	std::string textureDirectory;
	//Only using diffuse for now

	// 1. diffuse maps
	std::vector<std::shared_ptr<Texture>> diffuseMaps = Engine->moduleTexture->LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", textureDirectory);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<std::shared_ptr<Texture>> specularMaps = Engine->moduleTexture->LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", textureDirectory);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<std::shared_ptr<Texture>> normalMaps = Engine->moduleTexture->LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", textureDirectory);
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<std::shared_ptr<Texture>> heightMaps = Engine->moduleTexture->LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", textureDirectory);
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
}
