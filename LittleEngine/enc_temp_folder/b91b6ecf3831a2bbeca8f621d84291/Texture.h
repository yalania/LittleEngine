#ifndef _TEXTURE_
#define _TEXTURE_
#include <string>

class Texture {
public:

	Texture() = default;
	~Texture() = default;
	Texture(Texture && texture) = default;
	Texture(const Texture & texture) = default;

	Texture& operator = (Texture && texture) = default;
	Texture& operator = (const Texture & texture) = default;

	unsigned int id = 0;
	std::string type;
	std::string path;
	unsigned int textureSize = 0;
	int width, height = 0;
};

#endif // !_TEXTURE_

