#ifndef _MODULE_TEXTURE_
#define _MODULE_TEXTURE_
#include "Module.h"
#include "Components/Texture.h"

#include <vector>
#include <string>
#include <assimp/scene.h>
class ModuleTexture : public Module {
public:
	bool Init() override;
	Texture LoadTexture(const char *texturePath, const std::string &directory = "");
	std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, std::string directory);
private:
	void GetCheckerboardTexture();
	std::vector<std::shared_ptr<Texture>> texturesLoaded;
public:
	unsigned int checkerboardTextureId;
};

#endif // !_MODULE_TEXTURE_

