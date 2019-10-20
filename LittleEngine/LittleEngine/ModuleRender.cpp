#include "ModuleRender.h"
#include "LittleEngine.h"
#include "GL/glew.h"
#include "ShaderProgram.h"
//SDL_GLContext glcontext;
ModuleRender::ModuleRender() {


}

bool ModuleRender::Init() {

	SDL_GLContext glcontext = SDL_GL_CreateContext(Engine->moduleWindow->window);
	glewInit();
	glClearColor(0.2, 0.2, 0.2, 1);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearDepth(1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_WIDTH);
	addVertexBufferObject();
	loadShaders();
	return true;
}

update_status ModuleRender::PreUpdate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;

}

update_status ModuleRender::Update() {
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	return UPDATE_CONTINUE;

}

update_status ModuleRender::PostUpdate() {

	SDL_GL_SwapWindow(Engine->moduleWindow->window);
	return UPDATE_CONTINUE;

}

//Only a triangle for now
void ModuleRender::addVertexBufferObject() {
	float buffer_data[] = { -0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f };

	glGenBuffers(1, &VBO);

	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void ModuleRender::loadShaders() {
	GLuint shaderProgram = ShaderProgram::loadShaderProgram("vertexShader.vert", "fragmentShader.frag");
	glUseProgram(shaderProgram);
}