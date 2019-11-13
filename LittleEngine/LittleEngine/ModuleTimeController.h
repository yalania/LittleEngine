#ifndef _MODULE_TIME_CONTROLLER_
#define _MODULE_TIME_CONTROLLER_
#include "Module.h"
#include "Utils/MicroTimer.h"
#include "Utils/MsTimer.h"
#include <vector>

class ModuleTimeController : public Module
{
public:
	ModuleTimeController() = default;
	~ModuleTimeController() = default;

	bool Init() override;
	update_status Update() override;
	update_status PostUpdate() override;
	void Pause();
	void Play();
	void AdvanceOneFrame();
	double GetRealTimeSinceStart();


	MsTimer deltaTime;
	float frameRateLog[60];
private:
	MsTimer realTimeClock;
	MsTimer gameTimeClock;
	MsTimer fpsTimer;

	//FrameRate;
	int frameRateIndex = 0;
	long totalNumberOfFrames = 0;
};



#endif // !_MODULE_TIME_CONTROLLER_

