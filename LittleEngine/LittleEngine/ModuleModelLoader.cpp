#include "ModuleModelLoader.h"

#include "Log.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

void ModuleModelLoader::LoadModel(std::string const &pathToModel, std::string const &pathToTexture) {
	Assimp::Importer import;
	/*const aiScene *scene = import.ReadFile(pathToModel, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG( "ERROR::ASSIMP::", import.GetErrorString());
		return;
	}
	//directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);*/
}

void ModuleModelLoader::processNode(aiNode *node, const aiScene *scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		//meshes.push_back(processMesh(mesh, scene));
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}

}