#include "VertexBufferObject.h"
#include <GL/glew.h>


VertexBufferObject::VertexBufferObject(){

	float vertices[] = {
		 0.5f, -0.5f, 0.0f, 
	    0.5f,  0.2f, 0.0f,  
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.2f, 0.0f  };
	unsigned int indices[] = {
		0,1,2,
		1,3,2
	};

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

VertexBufferObject::~VertexBufferObject() {
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Update(){
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
