#include "MsTimer.h"
#include "../Log.h"

void MsTimer::Start() {
	LOG("Started timer");
	millis = SDL_GetTicks() * 1000;
}
double MsTimer::Read() {
	//LOG("Reading time since timer start");
	Uint32 current = SDL_GetTicks()* 1000;
	return static_cast<double>(current - millis);
}

void MsTimer::Stop() {
	LOG("Stop timer");
	millis = 0.0f;
}