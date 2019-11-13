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
	void LimitFrameRate();
	void Pause();
	void Play();
	void AdvanceOneFrame();


	//Timers
	MsTimer realTimeClock;
	MsTimer gameTimeClock;
	MsTimer fpsTimer;
	float frameRateLog[60];

private:

	//FrameRate;
	long totalNumberOfFrames = 0;
	int frameRateIndex = 0;

	//Delta
	float deltaTime;
	float realDeltaTime;
	float frameStartTime;
	float frameEndTime;

};



#endif // !_MODULE_TIME_CONTROLLER_

