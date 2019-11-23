#ifndef _MODULE_MODEL_LOADER_
#define _MODULE_MODEL_LOADER_
#include "Module.h"
#include <string>
#include <assimp/scene.h>
#include "Components/Mesh.h"
#include "Log.h"
#include <assimp/Importer.hpp>

class ModuleModelLoader : public Module {
public:
	ModuleModelLoader() = default;
	~ModuleModelLoader() {
		CleanUp();
	}
	bool Init() override;
	bool CleanUp() override;
	std::vector<Mesh> LoadModel(std::string const &pathToModel, std::string const &pathToTexture = "");
private:
	void ProcessNode(const aiNode &node, const aiScene &scene, std::vector<Mesh> & meshes) const;
	Mesh ProcessMesh(const aiMesh &mesh, const aiScene &scene) const;
	void ProcessMaterial(std::vector<std::shared_ptr<Texture>> &textures, const aiMesh &mesh, const aiScene &scene) const;

	std::string textureDirectory;
	std::unique_ptr<Assimp::Importer> import = std::make_unique<Assimp::Importer>();
};
#endif // !_MODULE_MODEL_LOADER_

