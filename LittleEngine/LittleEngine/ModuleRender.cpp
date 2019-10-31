#include "ModuleRender.h"
#include "LittleEngine.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

bool ModuleRender::Init() {

	InitOpenGlOptions();
	objects.push_back(std::make_unique<VertexBufferObject>());
	GenerateMatrices();
	return true;
}

update_status ModuleRender::PreUpdate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;

}

update_status ModuleRender::Update() {
	LoadShaders();
	for (auto &object : objects) {
		object->Update();
	}
	
	return UPDATE_CONTINUE;

}

update_status ModuleRender::PostUpdate() {

	SDL_GL_SwapWindow(Engine->moduleWindow->window);

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
			WindowResized(event.window.data1, event.window.data2);
		}
	}
	return UPDATE_CONTINUE;

}

void ModuleRender::LoadShaders() const{


	glUseProgram(Engine->moduleShaderProgram->defaultProgram);

	GLuint modelOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"model");
	GLuint viewOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"view");
	GLuint projOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"proj");
	glUniformMatrix4fv(modelOutput, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewOutput, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projOutput, 1, GL_FALSE, glm::value_ptr(projection));

}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
	aspect = width / height;
	glViewport(0, 0, width, height);
}

void ModuleRender::InitOpenGlOptions() const{

	SDL_GLContext glcontext = SDL_GL_CreateContext(Engine->moduleWindow->window);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		LOG("Error: %s\n", glewGetErrorString(err));
	}
	glClearColor(0.2, 0.2, 0.2, 1);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearDepth(1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_WIDTH);
}

bool ModuleRender::CleanUp() {
	return true;
}

void ModuleRender::GenerateMatrices(){
	
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);


	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	

	view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));


}