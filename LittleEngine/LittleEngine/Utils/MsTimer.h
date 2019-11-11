#ifndef _UTILS_MSTIMER_
#define _UTILS_MSTIMER_
#include <SDL/SDL.h>
class MsTimer {

public:
	MsTimer() = default;
	~MsTimer() = default;
	void Start();
	double Read();
	void Stop();

private:
	Uint32 millis = 0.0f;
};

#endif // !_UTILS_MSTIMER_

