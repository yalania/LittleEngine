#include "ModuleRender.h"
#include "LittleEngine.h"
#include "GL/glew.h"
#include "MathGeoLib/include/Geometry/Frustum.h"
#include "MathGeoLib/include/Math/float3x3.h"
#include "MathGeoLib/include/Math/float4.h"
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
	glUniformMatrix4fv(modelOutput, 1, GL_TRUE, &model.v[0][0]);
	glUniformMatrix4fv(viewOutput, 1, GL_TRUE, &view.v[0][0]);
	glUniformMatrix4fv(projOutput, 1, GL_TRUE, &projection.v[0][0]);

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
	Frustum frustum;
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;

	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = M_PI / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) *aspect);
	
	projection = frustum.ProjectionMatrix();

	
	model = float4x4( float4(2.0f,0.0f,0.0f,0.0f), 
		float4(0.0f, 1.0f, 0.0f, 0.0f),
		float4(0.0f, 0.0f, 1.0f, 0.0f),
		float4(0.0f, 0.0f, 0.0f, 1.0f));
		//float4x4::FromTRS(float3(0.0f, 0.0f, -4.0f),float3x3::RotateY((float)M_PI / 4.0f), float3(1.0f,1.0f, 1.0f));
	
	view = float4x4(float4(1.0f, 0.0f, 0.0f, 0.0f),
		float4(0.0f, 1.0f, 0.0f, 0.0f),
		float4(0.0f, 0.0f, 1.0f, 0.0f),
		float4(0.0f, 0.0f, 0.0f, 1.0f));
		//float4x4::LookAt(math::float3(1.0f, 1.0f, 1.0f), math::float3(1.0f, 1.0f, 1.0f),math::float3(1.0f, 1.0f, 1.0f), math::float3(1.0f,1.0f, .0f));


}