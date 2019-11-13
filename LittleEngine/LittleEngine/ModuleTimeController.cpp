#include "ModuleTimeController.h"


bool ModuleTimeController::Init() {
	realTimeClock.Start();
	gameTimeClock.Start();
	fpsTimer.Start();
	return true;
}


update_status ModuleTimeController::Update() {
	float avgFPS = totalNumberOfFrames / (fpsTimer.Read() / 1000.f);
	frameRateLog[frameRateIndex] = avgFPS;
	++frameRateIndex;
	if (frameRateIndex > 60) {
		frameRateIndex = 0;
	}
	return UPDATE_CONTINUE;
}
update_status ModuleTimeController::PostUpdate() {
	totalNumberOfFrames++;
	return UPDATE_CONTINUE;
}
void ModuleTimeController::Pause() {

}

void ModuleTimeController::Play() {

}

void ModuleTimeController::AdvanceOneFrame() {

}

double ModuleTimeController::GetRealTimeSinceStart() {
	return realTimeClock.Read();
}
