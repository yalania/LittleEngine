#include "VertexBufferObject.h"
#include "GL/glew.h"


VertexBufferObject::VertexBufferObject(){

	float vertex[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f };

	glGenBuffers(1, &VBO);

	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
VertexBufferObject::~VertexBufferObject(){
}

void VertexBufferObject::Update(){
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
