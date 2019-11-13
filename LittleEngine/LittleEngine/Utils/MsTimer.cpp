#include "MsTimer.h"

void MsTimer::Start() {
	timeInMillis = static_cast<double>(SDL_GetTicks());
}
double MsTimer::Read() {
	double current = static_cast<double>(SDL_GetTicks());
	return static_cast<double>(current - timeInMillis);
}
