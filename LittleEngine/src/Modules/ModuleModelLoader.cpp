#include "ModuleModelLoader.h"
#include "LittleEngine.h"
#include <assimp/DefaultLogger.hpp>
#include <assimp/postprocess.h>

bool ModuleModelLoader::Init() {
	static unsigned int flags = Assimp::Logger::VERBOSE | Assimp::Logger::Err | Assimp::Logger::Warn | Assimp::Logger::Debugging;
	Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
	Assimp::DefaultLogger::get()->attachStream(new AssimpLog(), flags);
	return true;
}

bool ModuleModelLoader::CleanUp() {
	Assimp::DefaultLogger::kill();
	return true;
}
std::vector<Mesh> ModuleModelLoader::LoadModel(std::string const &pathToModel, std::string const &pathToTexture){
	std::vector<Mesh> meshes;

	const aiScene *scene = import->ReadFile(pathToModel, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG( "ERROR::ASSIMP::%s", import->GetErrorString());
		return meshes;
	}

	size_t endPosition = pathToModel.find_last_of('\\');
	if (pathToTexture != "" || endPosition > pathToModel.size() || endPosition <= 0) {
		textureDirectory = pathToTexture;
	}
	else {
		textureDirectory = pathToModel.substr(0, endPosition);
	}

	ProcessNode(*scene->mRootNode, *scene, meshes);
	return meshes;
}

void ModuleModelLoader::ProcessNode(const aiNode &node, const aiScene &scene, std::vector<Mesh> & meshes) const
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node.mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene.mMeshes[node.mMeshes[i]];
		meshes.emplace_back(ProcessMesh(*mesh, scene));
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node.mNumChildren; i++)
	{
		ProcessNode(*node.mChildren[i], scene, meshes); //Recursive!!
	}

}

Mesh ModuleModelLoader::ProcessMesh(const aiMesh &mesh, const aiScene &scene) const
{
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::shared_ptr<Texture>> textures;
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
	ProcessMaterial(textures, mesh, scene);

	scene.mMaterials[mesh.mMaterialIndex];
	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures, MeshInfo{ mesh.mNumVertices, mesh.mNumFaces, mesh.mName.C_Str()});
}

void ModuleModelLoader::ProcessMaterial(std::vector<std::shared_ptr<Texture>> &textures, const aiMesh &mesh, const aiScene &scene) const{
	
	// process materials
	aiMaterial* material = scene.mMaterials[mesh.mMaterialIndex];

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
