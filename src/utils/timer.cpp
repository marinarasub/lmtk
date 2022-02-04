#include "timer.h"

namespace utils {

	Timer::Timer()
	{
	}

	void Timer::start()
	{
		start_point = hrc::now();
	}

	double Timer::time()
	{
		hrc::time_point end_point = hrc::now();
		duration<double> elapsed = end_point - start_point;
		return elapsed.count();
	}

}