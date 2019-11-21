#include "ModuleTexture.h"
#include "LittleEngine.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include "Log.h"

bool ModuleTexture::Init() {
	GetCheckerboardTexture();
	return true;
}

Texture ModuleTexture::LoadTexture(const char *texturePath, const std::string &directory) {
	std::string filename = std::string(texturePath);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	LOG("Loading texture %s . Looking in path describe in fbx", texturePath);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

	size_t endPosition = filename.find_last_of('\\');
	std::string textureName;
	if (endPosition > filename.size() || endPosition <= 0) {
		textureName = filename;
	}
	else {
		textureName = filename.substr(endPosition, -1);
	}
	if (!data) {
		filename = directory + '\\' + textureName;
		LOG("Loading texture %s . Looking in same path as fbx", textureName);
		data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	}
	if (!data) {
		filename = "Textures\\" + textureName;
		LOG("Loading texture %s . Looking in Textures folder", textureName);
		data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	}
	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}else if(nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else if (nrChannels == 1) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("Failed to load texture");
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	GLuint textureOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"textureImg");
	glUniform1i(textureOutput, texture);

	return 	Texture{ texture,"",filename, 0, width, height };
}


std::vector<std::shared_ptr<Texture>> ModuleTexture::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, std::string directory)
{
	std::vector<std::shared_ptr<Texture>> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < texturesLoaded.size(); j++)
		{
			if (std::strcmp(texturesLoaded[j]->path.data(), str.C_Str()) == 0)
			{
				textures.push_back(texturesLoaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			std::shared_ptr<Texture> texture = std::make_shared<Texture>(LoadTexture(str.C_Str(), directory));
			texture->type = typeName;
			texture->path = str.C_Str();
			texture->textureSize = mat->mNumAllocated;
			textures.push_back(texture);
			texturesLoaded.push_back(texture); // add to loaded textures
		}
	}
	return textures;
}

void ModuleTexture::GetCheckerboardTexture() {
	const static int checkerHeight = 64;
	const static int checkWidth = 64;

	static GLubyte checkImage[checkerHeight][checkWidth][3];
	int i, j, color;
	for (i = 0; i < checkerHeight; i++) {
		for (j = 0; j < checkWidth; j++) {
			color = ((((i & 0x4) == 0) ^ ((j & 0x4)) == 0)) * 255; // 0 -> black or 255 white
			checkImage[i][j][0] = (GLubyte)color; //R
			checkImage[i][j][1] = (GLubyte)color; //G
			checkImage[i][j][2] = (GLubyte)color; //B
		}
	}

	glGenTextures(1, &checkerboardTextureId);
	glBindTexture(GL_TEXTURE_2D, checkerboardTextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, checkerHeight,checkWidth, 0, GL_RGB, GL_UNSIGNED_BYTE,checkImage);
	glBindTexture(GL_TEXTURE_2D, 0);
}