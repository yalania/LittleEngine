#include "ModuleTimeController.h"


bool ModuleTimeController::Init() {
	realTimeClock.Start();
	gameTimeClock.Start();
	fpsTimer.Start();
	return true;
}


update_status ModuleTimeController::Update() {
	frameStartTime = gameTimeClock.Read();
	float avgFPS = totalNumberOfFrames / (fpsTimer.Read() / 1000.f);
	frameRateLog[frameRateIndex] = avgFPS;
	++frameRateIndex;
	if (frameRateIndex > 60) {
		frameRateIndex = 0;
	}
	return UPDATE_CONTINUE;
}
update_status ModuleTimeController::PostUpdate() {
	++totalNumberOfFrames;
	if (totalNumberOfFrames < 0){
		totalNumberOfFrames = 0;
		fpsTimer.Start();
	}
	return UPDATE_CONTINUE;
}

void ModuleTimeController::LimitFrameRate() {
	frameEndTime = gameTimeClock.Read();
	deltaTime = frameEndTime - frameStartTime;

	if (LIMIT_FRAME_RATE && deltaTime < SCREEN_TICK_PER_FRAME)
	{
		//Wait remaining time
		SDL_Delay(SCREEN_TICK_PER_FRAME - deltaTime);
	}
}

void ModuleTimeController::Pause() {

}

void ModuleTimeController::Play() {

}

void ModuleTimeController::AdvanceOneFrame() {

}

