#include "Time.h"

std::chrono::time_point<std::chrono::high_resolution_clock> resettime;

void resetTime()
{
	resettime = high_resolution_clock::now();
}

void showTime()
{
	auto currtime = high_resolution_clock::now();
	duration<double, std::milli> ms = currtime - resettime;
	cout << ms.count() << " ms";
}