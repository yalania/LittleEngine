#include "MicroTimer.h"

void MicroTimer::Start() {
	timeInMillis = static_cast<double>(SDL_GetPerformanceCounter() * 1000) / SDL_GetPerformanceFrequency();
}

double MicroTimer::Read() {
	double current = static_cast<double>(SDL_GetPerformanceCounter() * 1000);
	return static_cast<double>((SDL_GetPerformanceCounter() - timeInMillis)/ SDL_GetPerformanceFrequency());
}

void MicroTimer::Pause() {
	if (started && !paused)
	{
		paused = true;
		float current = static_cast<double>(SDL_GetPerformanceCounter() * 1000) / SDL_GetPerformanceFrequency();
		pausedTimeInMillis = current - pausedTimeInMillis;
		timeInMillis = 0;
	}
}

void MicroTimer::UnPause() {
	if (started && paused)
	{
		paused = false;
		float current = static_cast<double>(SDL_GetPerformanceCounter() * 1000) / SDL_GetPerformanceFrequency();
		timeInMillis = current - pausedTimeInMillis;
		pausedTimeInMillis = 0;
	}
}
