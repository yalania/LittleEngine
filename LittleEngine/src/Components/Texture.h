#ifndef _TEXTURE_
#define _TEXTURE_
#include <string>

class Texture {
public:

	Texture() = default;
	Texture(unsigned int id, std::string type, std::string path, std::string name,unsigned int textureSize,int width, int height) :
	id(id), type(type), path(path), name(name),textureSize(textureSize), width(width), height(height)
	{

	}
	~Texture()= default;
	Texture(Texture && texture) = default;
	Texture(const Texture & texture) = default;

	Texture& operator = (Texture && texture) = default;
	Texture& operator = (const Texture & texture) = default;

	std::string type = "";
	std::string path = "";
	std::string name = "";
	unsigned int id = 0;
	unsigned int textureSize = 0;
	int width, height = 0;
};

#endif // !_TEXTURE_

