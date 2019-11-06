#include "ModuleTexture.h"
#include "LittleEngine.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

update_status ModuleTexture::Update() {
	glBindTexture(GL_TEXTURE_2D, texture);
	return UPDATE_CONTINUE;
}

void ModuleTexture::LoadTexture(const char * texturePath) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}else if(nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("Failed to load texture");
	}
	stbi_image_free(data);

	GLuint textureOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"textureImg");
	glUniform1i(textureOutput, texture);
}