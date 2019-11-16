#include <SDL/SDL.h>
#include <GL/glew.h>
#include "SystemProperties.h"


std::string SystemProperties::GetSystemCPUs() {
	std::string cpuCount = std::to_string(SDL_GetCPUCacheLineSize());
	std::string cpuCache = std::to_string(SDL_GetCPUCount());
	return cpuCount + "(Cache: "+ cpuCache + "kb)";
}


std::string SystemProperties::GetSystemCaps() {
	std::string caps;
	if (SDL_Has3DNow()) {
		caps.append("3DNow, ");
	}
	if (SDL_HasAltiVec()) {
		caps.append("AltiVec, ");
	}
	if (SDL_HasAVX2()) {
		caps.append("AVX2, ");
	}
	if (SDL_HasAVX()) {
		caps.append("AVX, ");
	}
	if (SDL_HasAVX512F()) {
		caps.append("AVX512F, ");
	}
	if (SDL_HasMMX()) {
		caps.append("MMX, ");
	}
	if (SDL_HasNEON()) {
		caps.append("NEON, ");
	}
	if (SDL_HasRDTSC()) {
		caps.append("RDTSC, ");
	}
	if (SDL_HasSSE()) {
		caps.append("SSE, ");
	}
	if (SDL_HasSSE2()) {
		caps.append("SSE2, ");
	}
	if (SDL_HasSSE3()) {
		caps.append("SSE3, ");
	}
	if (SDL_HasSSE41()) {
		caps.append("SSE41, ");
	}
	if (SDL_HasSSE42()) {
		caps.append("SSE42, ");
	}
	return caps;
}

std::string SystemProperties::GetSystemGPU() {
	return std::string(reinterpret_cast<char const*>(glGetString(GL_RENDERER)));
}
std::string SystemProperties::GetSystemGPUBrand(){
	return std::string(reinterpret_cast<char const*>(glGetString(GL_VENDOR)));
}


float SystemProperties::GetSystemRam(){
	return SDL_GetSystemRAM() / 1000.0f;
}
float SystemProperties::GetVRAMBudget(){
	return 0;
}
float SystemProperties::GetVRAMUsage() { return 0; }
float SystemProperties::GetVRAMAvailable(){
	int availableKB[4];
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &availableKB[0]);
	return 0;
}
float SystemProperties::GetVRAMReserved(){
	return 0;
}