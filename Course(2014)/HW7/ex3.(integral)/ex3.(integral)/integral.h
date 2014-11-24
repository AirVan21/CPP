#include <functional>
// Class represents integral 

class Integral
{
	// Pointre for double function
	typedef double(*dfunction)(double);
	
	static const double epsilon;

public:
	Integral(int lowLim = 0, int topLim = 1);
	double calculate(const dfunction);

private:
	// Defines intergation interval
	double mLowLim;
	double mTopLim;
};

