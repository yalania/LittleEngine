#include "ModuleRender.h"
#include "LittleEngine.h"
#include "GL/glew.h"

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
	return true;
}

update_status ModuleRender::PreUpdate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;

}

update_status ModuleRender::Update() {


	return UPDATE_CONTINUE;

}

update_status ModuleRender::PostUpdate() {

	SDL_GL_SwapWindow(Engine->moduleWindow->window);
	return UPDATE_CONTINUE;

}