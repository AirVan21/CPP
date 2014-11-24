#include "integral.h"

const double Integral::epsilon = 0.01;

Integral::Integral(int lowLim, int topLim) : 
	mLowLim(lowLim),
	mTopLim(topLim)
{}

// Calculating intergal, using trapeze method
double Integral::calculate(const dfunction func)
{
	double step = (mTopLim - mLowLim) * epsilon;
	double heightSum = 0;
	for (double i = mLowLim + step; i < mTopLim; i += step) {
		heightSum += func(i);
	}
	double edgeSum = 0.5 * (func(mLowLim) + func(mTopLim));
	return (edgeSum + heightSum) * step;
}
