#include <iostream>
#include <exception>

// Represents Time class
class Time
{

public:
	// Constructor
	Time(int hour, int minute);
	~Time();
	// Prints Time
	void print() const;

private:

	int mHour;

	int mMinute;

};
