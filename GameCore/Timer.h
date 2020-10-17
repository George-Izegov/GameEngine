#pragma once


class Timer
{
public:
	Timer();

protected:
	double PCFreq;
	__int64 CounterStart;

public:
	void StartCounter();
	double GetCounter();

};