#ifndef _VERTEX_BUFFER_OBJECT
#define _VERTEX_BUFFER_OBJECT

#include "Module.h"
class VertexBufferObject {

public:
	VertexBufferObject();
	~VertexBufferObject();

	void Update();

private:
	unsigned int VBO = 0;
	unsigned int EBO = 0;
	unsigned int VAO = 0;
	unsigned int texture = 0;

};
#endif // !_VERTEX_BUFFER_OBJECT

