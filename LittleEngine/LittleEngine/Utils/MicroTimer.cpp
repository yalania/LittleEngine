#include "MicroTimer.h"
#include "../Log.h"

void MicroTimer::Start() {
	LOG("Started timer");
	micro = SDL_GetPerformanceCounter() * 1000;
}
double MicroTimer::Read() {
	//LOG("Reading time since timer start");
	Uint64 current = SDL_GetPerformanceCounter() * 1000;
	return static_cast<double>(SDL_GetPerformanceCounter() - micro);
}

void MicroTimer::Stop() {
	LOG("Stop timer");
	micro = 0.0f;
}
