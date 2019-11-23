#include "ModuleRender.h"
#include "LittleEngine.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

bool ModuleRender::Init() {
	LOG("Init Render system");
	InitOpenGlOptions();
	return true;
}

void ModuleRender::AddGameObject(const char * model) {
	Model newModel = Engine->moduleModelLoader->LoadModel(model);
	gameObjects.erase(gameObjects.begin(), gameObjects.end()); //ASSIMENT: For now because the assiment requirements
	gameObjects.push_back(std::make_unique<GameObject>(newModel, Engine->moduleShaderProgram->defaultProgram));
	Engine->moduleCamera->FocusOnGameObject(*gameObjects.back());
}
update_status ModuleRender::PreUpdate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;

}

update_status ModuleRender::Update() {
	for (auto & gameObject : gameObjects) {
		gameObject->Update();
	}
	return UPDATE_CONTINUE;

}

update_status ModuleRender::PostUpdate() {
	SDL_GL_SwapWindow(Engine->moduleWindow->window);
	return UPDATE_CONTINUE;
}

void ModuleRender::InitOpenGlOptions() const{

	SDL_GLContext glcontext = SDL_GL_CreateContext(Engine->moduleWindow->window);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		LOG("Error: %s\n", glewGetErrorString(err));
	}
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearDepth(1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Enable the debug callback
	/*glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); Disable for now as it blocks mouse buttons events
	glDebugMessageCallback(OurOpenGLErrorFunction, nullptr);
	glDebugMessageControl(
		GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true
	);*/
}

bool ModuleRender::CleanUp() {
	SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
	return true;
}

GameObject& ModuleRender::GetGameObject() const {
	if (gameObjects.size() > 0) {
		return *gameObjects.front();
	}
	else {
		return *missingGameObject.get();
	}
}

ModuleRender::~ModuleRender() {
	CleanUp();
}

void ModuleRender::EnableFaceCulling(bool faceCullingEnabled){
	if (faceCullingEnabled) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

}

void ModuleRender::EnableClockwiseFaceCulling(bool clockwiseFaceCullingEnabled) {
	if (clockwiseFaceCullingEnabled) {
		glFrontFace(GL_CW);
	}
	else {
		glFrontFace(GL_CCW);
	}
}

void ModuleRender::SelectFillingMode(int mode) {
	if (mode == 0) {
		glPolygonMode(GL_FRONT,GL_FILL);
	}
	if(mode == 1){
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	if (mode == 2) {
		glPolygonMode(GL_FRONT, GL_POINT);
	}
}

void ModuleRender::ProcessFile(const char * file) {
	std::string fileExtension = std::string(file).substr(std::string(file).find_last_of('.'), -1);
	std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(),::tolower);
	if (fileExtension == ".fbx") {
		AddGameObject(file);
		Engine->moduleCamera->FocusOnGameObject(GetGameObject());
	}
	else {
		GetGameObject().model->ChangeTexture(Engine->moduleTexture->LoadTexture(file));

	}
}