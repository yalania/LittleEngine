#include "ModuleRender.h"
#include "LittleEngine.h"
#include "GL/glew.h"

bool ModuleRender::Init() {

	InitOpenGlOptions();
	objects.push_back(std::make_unique<VertexBufferObject>());
	LoadShaders();
	return true;
}

update_status ModuleRender::PreUpdate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;

}

update_status ModuleRender::Update() {
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
}

void ModuleRender::WindowResized(unsigned width, unsigned height) const
{
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