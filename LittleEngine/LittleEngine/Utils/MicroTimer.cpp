#include "MicroTimer.h"

void MicroTimer::Start() {
	timeInMillis = static_cast<double>(SDL_GetPerformanceCounter() * 1000) / SDL_GetPerformanceFrequency();
}
double MicroTimer::Read() {
	double current = static_cast<double>(SDL_GetPerformanceCounter() * 1000);
	return static_cast<double>((SDL_GetPerformanceCounter() - timeInMillis)/ SDL_GetPerformanceFrequency());
}
