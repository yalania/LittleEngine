#ifndef _UTILS_MICROTIMER_
#define _UTILS_MICROTIMER_
#include <SDL/SDL.h>
#include "Timer.h"
class MicroTimer : public Timer {

public:
	MicroTimer() = default;
	~MicroTimer() = default;
	void Start() override;
	double Read() override;
};

#endif // !_UTILS_MICROTIMER_
