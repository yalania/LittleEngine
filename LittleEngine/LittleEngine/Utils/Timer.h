#ifndef _TIMER_
#define _TIMER_

class Timer {

public:
	Timer() = default;
	virtual ~Timer() = default;
	virtual void Start() {}
	virtual double Read() { return timeInMillis; }

	virtual double Stop() {
		double current = Read();
		timeInMillis = 0.0f;
		return current;
	}

protected:
	double timeInMillis = 0.0f;
};

#endif // !_TIMER_

