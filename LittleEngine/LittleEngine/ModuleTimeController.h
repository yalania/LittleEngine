#ifndef _MODULE_TIME_CONTROLLER_
#define _MODULE_TIME_CONTROLLER_
#include "Module.h"
#include "Utils/MicroTimer.h"
#include "Utils/MsTimer.h"

class ModuleTimeController : public Module
{
public:
	ModuleTimeController() = default;
	~ModuleTimeController() = default;

	bool Init() override;
	void Pause();
	void Play();
	void AdvanceOneFrame();

private:
	MsTimer realTimeClock;
	MsTimer gameTimeClock;
};



#endif // !_MODULE_TIME_CONTROLLER_

