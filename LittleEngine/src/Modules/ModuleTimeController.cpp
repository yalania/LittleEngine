#include "ModuleTimeController.h"

bool ModuleTimeController::Init() {
	realTimeClock.Start();
	gameTimeClock.Start();
	fpsTimer.Start();
	return true;
}

UpdateStatus ModuleTimeController::PreUpdate() {
	frameStartTime = fpsTimer.Read();
	float avgFPS = static_cast<float>(totalNumberOfFrames / (fpsTimer.Read() / 1000.f));
	frameRateLog[frameRateIndex] = avgFPS;
	++frameRateIndex;
	if (frameRateIndex > 60) {
		frameRateIndex = 0;
	}
	return UpdateStatus::UPDATE_CONTINUE;
}
UpdateStatus ModuleTimeController::PostUpdate() {
	++totalNumberOfFrames;
	--advanceOnFrameCounter;
	return UpdateStatus::UPDATE_CONTINUE;
}

void ModuleTimeController::LimitFrameRate() {
	frameEndTime = fpsTimer.Read();
	deltaTime = frameEndTime - frameStartTime;

	if (LIMIT_FRAME_RATE && deltaTime < SCREEN_TICK_PER_FRAME)
	{
		//Wait remaining time
		SDL_Delay(static_cast<UINT32>(SCREEN_TICK_PER_FRAME - deltaTime));
	}

	if (advanceOnFrameActivated && advanceOnFrameCounter <= 0) {
		advanceOnFrameActivated = false;
		gameIsPaused = true;
		gameTimeClock.Pause();
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
	AdvanceFrames(1);
}

void ModuleTimeController::AdvanceFrames(int numberOfFramesToAdvance) {
	if (gameIsPaused) {
		advanceOnFrameActivated = true;
		gameIsPaused = false;
		gameTimeClock.UnPause();
		advanceOnFrameCounter = numberOfFramesToAdvance;
	}
}
