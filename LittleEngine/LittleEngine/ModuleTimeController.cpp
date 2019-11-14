#include "ModuleTimeController.h"

bool gameIsPaused = false;
bool ModuleTimeController::Init() {
	realTimeClock.Start();
	gameTimeClock.Start();
	fpsTimer.Start();
	return true;
}

update_status ModuleTimeController::Update() {
	frameStartTime = fpsTimer.Read();
	float avgFPS = static_cast<float>(totalNumberOfFrames / (fpsTimer.Read() / 1000.f));
	frameRateLog[frameRateIndex] = avgFPS;
	++frameRateIndex;
	if (frameRateIndex > 60) {
		frameRateIndex = 0;
	}
	return UPDATE_CONTINUE;
}
update_status ModuleTimeController::PostUpdate() {
	++totalNumberOfFrames;
	if(advanceOnFrameActivated)
	return UPDATE_CONTINUE;
}

void ModuleTimeController::LimitFrameRate() {
	frameEndTime = fpsTimer.Read();
	deltaTime = frameEndTime - frameStartTime;

	if (LIMIT_FRAME_RATE && deltaTime < SCREEN_TICK_PER_FRAME)
	{
		//Wait remaining time
		SDL_Delay(static_cast<UINT32>(SCREEN_TICK_PER_FRAME - deltaTime));
	}
}

void ModuleTimeController::Pause() {
	if (!gameIsPaused) {
		gameIsPaused = true;
		gameTimeClock.Pause();
	}
}

void ModuleTimeController::Play() {
	if (gameIsPaused) {
		gameIsPaused = false;
		gameTimeClock.UnPause();
	}
}

void ModuleTimeController::AdvanceOneFrame() {
	advanceOnFrameActivated = true;
}

