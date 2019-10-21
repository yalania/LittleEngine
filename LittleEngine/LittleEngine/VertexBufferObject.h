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
};
#endif // !_VERTEX_BUFFER_OBJECT

