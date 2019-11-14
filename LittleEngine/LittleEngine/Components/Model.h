#ifndef _MODEL_COMPONENT_
#define _MODEL_COMPONENT_

#include "Component.h"
#include <vector>
#include "Mesh.h"
class Model : public Component {

public:
	Model(std::vector<Mesh> entityMeshes);
	update_status Update() override;

private:
	std::vector<Mesh> entityMeshes;
};
#endif // !_MODEL_COMPONENT_

