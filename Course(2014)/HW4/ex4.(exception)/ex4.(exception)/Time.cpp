#include "time.h"

Time::Time(int hour, int minute) 
{
	if (hour < 0 || 24 < hour) {
		throw "Wrong hour parametr!\n";
	}

	if (minute < 0 || 59 < minute) {
		throw std::exception("Wrong minute parametr!\n");
	}
	mHour = hour;
	mMinute = minute;
}

void Time::print() const
{
	std::cout << "( " << mHour << " , " << mMinute << " )\n";
}

Time::~Time()
{
}