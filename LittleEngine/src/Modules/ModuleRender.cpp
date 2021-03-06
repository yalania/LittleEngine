#include "ModuleRender.h"
#include "LittleEngine.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <Modules/ModuleWindow.h>

bool ModuleRender::Init() {
	LOG("Init Render system");
	InitOpenGlOptions();
	return true;
}


UpdateStatus ModuleRender::PreUpdate() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UpdateStatus::UPDATE_CONTINUE;

}

UpdateStatus ModuleRender::Update() {
	glUseProgram(Engine->moduleShaderProgram->defaultProgram);
	for (auto & mesh : meshesComponent) {
		mesh->Update();
	}
	glUseProgram(0);
	return UpdateStatus::UPDATE_CONTINUE;

}

UpdateStatus ModuleRender::PostUpdate() {
	SDL_GL_SwapWindow(Engine->moduleWindow->window);
	return UpdateStatus::UPDATE_CONTINUE;
}


void ModuleRender::AddMeshComponentToGameObject(GameObject * gameObject) {
	if (gameObject->GetComponents(ComponentType::MESH).size() < 1) {
		meshesComponent.push_back(std::make_unique<Mesh>(gameObject));
	}
}

void ModuleRender::CreateMeshComponentFromFile(const char * file) {
	std::vector<Mesh> meshes = Engine->moduleModelLoader->LoadModel(file);
	for (auto & mesh : meshes) {
		GameObject * newGameObject = Engine->moduleSceneManager->CreateGameObject();
		std::unique_ptr<Mesh> uniqueMesh = std::make_unique<Mesh>(std::move(mesh));
		uniqueMesh->SetOwner(newGameObject);
		meshesComponent.push_back(std::move(uniqueMesh));
	}
}

void ModuleRender::RemoveMeshComponent(Mesh * componentToRemove){
	auto it = std::remove_if(meshesComponent.begin(), meshesComponent.end(), [componentToRemove](auto const & mesh)
	{
		return mesh.get() == componentToRemove;
	});
	meshesComponent.erase(it);
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

