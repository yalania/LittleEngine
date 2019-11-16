#ifndef _SYSTEM_PROPERTIES_
#define _SYSTEM_PROPERTIES_
#include <string>
class SystemProperties {
public:
	SystemProperties() = default;
	~SystemProperties() = default;
	std::string GetSystemCPUs();
	float GetSystemRam();
	std::string GetSystemCaps();

	std::string GetSystemGPU();
	std::string GetSystemGPUBrand();
	float GetVRAMBudget();
	float GetVRAMUsage();
	float GetVRAMAvailable();
	float GetVRAMReserved();

};

#endif // !_SYSTEM_PROPERTIES_

