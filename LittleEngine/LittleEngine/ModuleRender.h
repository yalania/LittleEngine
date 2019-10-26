#ifndef _MODULE_RENDER_
#define _MODULE_RENDER_
#include "Module.h"
#include "VertexBufferObject.h"
#include <vector>
#include <memory>
#include "MathGeoLib/include/Math/float4x4.h"


class ModuleRender : public Module {
public:
	ModuleRender() = default;
	~ModuleRender() = default;

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;
	void WindowResized(unsigned width, unsigned height);


private:
	void LoadShaders() const;
	void InitOpenGlOptions() const;
	void GenerateMatrices();

private:
	std::vector<std::unique_ptr<VertexBufferObject>> objects;
	float4x4 projection;
	float4x4 model;
	float4x4 view;
	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;

};

#endif // !_MODULE_RENDER_

