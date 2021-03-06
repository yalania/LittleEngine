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
	UpdateStatus PreUpdate() override;
	UpdateStatus PostUpdate() override;
	void LimitFrameRate();
	void Pause();
	void Play();
	void AdvanceOneFrame();
	void AdvanceFrames(int numberOfFramesToAdvance);


	//Timers
	float frameRateLog[60];
	MsTimer realTimeClock;
	MsTimer gameTimeClock;
	MsTimer fpsTimer;

	double deltaTime;
private:

	//FrameRate;
	uint64_t totalNumberOfFrames = 0;
	int frameRateIndex = 0;

	//Delta
	double realDeltaTime;
	double frameStartTime;
	double frameEndTime;

	bool advanceOnFrameActivated = false;
	int advanceOnFrameCounter = 0;
};



#endif // !_MODULE_TIME_CONTROLLER_

