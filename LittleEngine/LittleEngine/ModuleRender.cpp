#include "ModuleRender.h"
#include "GL/glew.h"
#include "LittleEngine.h"

ModuleRender::ModuleRender() {


}

bool ModuleRender::Init() {
	glewInit();
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearDepth(1.0f);
	glClearColor(0.f, 1.f, 0.f, 1.f);
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