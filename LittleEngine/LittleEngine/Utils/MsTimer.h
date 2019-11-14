#ifndef _UTILS_MSTIMER_
#define _UTILS_MSTIMER_
#include <SDL/SDL.h>
#include "Timer.h"
class MsTimer : public Timer{

public:
	MsTimer() = default;
	~MsTimer() = default;
	void Start() override;
	double Read() override;

	void Pause() override;
	void UnPause() override;
};

#endif // !_UTILS_MSTIMER_

