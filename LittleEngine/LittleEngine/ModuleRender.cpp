#include "ModuleRender.h"
#include "LittleEngine.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

bool ModuleRender::Init() {
	LOG("Init render system");
	InitOpenGlOptions();
	objects.push_back(std::make_unique<VertexBufferObject>());
	GenerateMatrices();
	return true;
}

update_status ModuleRender::PreUpdate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	LoadShaders();
	return UPDATE_CONTINUE;

}

update_status ModuleRender::Update() {
	ShowDirectionArrows();
	ShowGrid();
	for (auto &object : objects) {
		object->Update();
	}
	return UPDATE_CONTINUE;

}

update_status ModuleRender::PostUpdate() {

	SDL_GL_SwapWindow(Engine->moduleWindow->window);

	return UPDATE_CONTINUE;

}

void ModuleRender::LoadShaders() const{


	glUseProgram(Engine->moduleShaderProgram->defaultProgram);

	GLuint modelOutput = glGetUniformLocation(Engine->moduleShaderProgram->defaultProgram,
		"model");
	glUniformMatrix4fv(modelOutput, 1, GL_FALSE, glm::value_ptr(model));
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
	Engine->moduleWindow->width = width;
	Engine->moduleWindow->height = height;
	Engine->moduleCamera->LoadProjection();
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
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Enable the debug callback
	glEnable(GL_DEBUG_OUTPUT);
	//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); Disable for now as it blocks mouse buttons events
	glDebugMessageCallback(OurOpenGLErrorFunction, nullptr);
	glDebugMessageControl(
		GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true
	);
}

bool ModuleRender::CleanUp() {
	SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
	return true;
}

void ModuleRender::GenerateMatrices(){
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	
}
void ModuleRender::ShowGrid() const {
	glLineWidth(1.0f);
	float d = 200.0f;
	glBegin(GL_LINES);
	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}
	glEnd();
}

void ModuleRender::ShowDirectionArrows() const {
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	// red X
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
	glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);
	// green Y
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

	// blue Z
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);
	glEnd();
	glLineWidth(1.0f);
}