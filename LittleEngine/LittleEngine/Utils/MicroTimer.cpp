#include "MicroTimer.h"
#include "../Log.h"

void MicroTimer::Start() {
	LOG("Started timer");
	millis = (SDL_GetPerformanceCounter() * 1000) / SDL_GetPerformanceFrequency();
}
double MicroTimer::Read() {
	//LOG("Reading time since timer start");
	Uint64 current = SDL_GetPerformanceCounter() * 1000;
	return static_cast<double>((SDL_GetPerformanceCounter() - millis)/ SDL_GetPerformanceFrequency());
}

void MicroTimer::Stop() {
	LOG("Stop timer");
	millis = 0.0f;
}
