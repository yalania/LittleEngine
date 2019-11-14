#ifndef _TIMER_
#define _TIMER_

class Timer {

public:
	Timer() = default;
	virtual ~Timer() = default;
	virtual void Start() { started = true; }
	virtual double Read() { return timeInMillis; }

	virtual void Pause(){}
	virtual void UnPause(){}
	virtual bool IsPaused() { return paused; };

	virtual double Stop() {
		double current = Read();
		timeInMillis = 0.0f;
		pausedTimeInMillis = 0.0f;
		paused = false;
		started = false;
		return current;
	}

protected:
	double timeInMillis = 0.0f;
	double pausedTimeInMillis = 0.0f;

	//The timer status
	bool paused = false;
	bool started = false;
};

#endif // !_TIMER_

