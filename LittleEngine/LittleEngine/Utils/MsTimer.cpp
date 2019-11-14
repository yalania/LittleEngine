#include "MsTimer.h"

void MsTimer::Start() {
	started = true;
	timeInMillis = static_cast<double>(SDL_GetTicks());
}

double MsTimer::Read() {
	double current = static_cast<double>(SDL_GetTicks());
	return static_cast<double>(current - timeInMillis);
}

void MsTimer::Pause() {
	if (started && !paused)
	{
		paused = true;
		pausedTimeInMillis = SDL_GetTicks() - timeInMillis;
		timeInMillis = 0;
	}
}

void MsTimer::UnPause(){
	if (started && paused)
	{
		paused = false;
		timeInMillis = SDL_GetTicks() - pausedTimeInMillis;
		pausedTimeInMillis = 0;
	}
}
