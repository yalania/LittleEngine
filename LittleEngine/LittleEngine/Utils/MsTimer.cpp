#include "MsTimer.h"

void MsTimer::Start() {
	millis = SDL_GetTicks();
}
double MsTimer::Read() {
	Uint32 current = SDL_GetTicks();
	return static_cast<double>(current - millis);
}

void MsTimer::Stop() {
	millis = 0.0f;
}