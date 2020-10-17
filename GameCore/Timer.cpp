#include "Timer.h"
#include <windows.h>
#include <ctime>
#include "time.h"
#include <iostream>

Timer::Timer()
{
	PCFreq = 0.0;
	CounterStart = 0;
}
void Timer::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";
	PCFreq = double(li.QuadPart);

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double Timer::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;

}