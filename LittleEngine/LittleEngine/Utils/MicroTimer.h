#ifndef _UTILS_MICROTIMER_
#define _UTILS_MICROTIMER_
#include <SDL/SDL.h>

class MicroTimer {

public:
	MicroTimer() = default;
	~MicroTimer() = default;
	void Start();
	double Read();
	void Stop();

private:
	Uint64 micro = 0.0f;
};

#endif // !_UTILS_MICROTIMER_
