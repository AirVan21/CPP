#include "rational.h"

Rational::Rational(int numer, int denom) :
	mNumerator(numer),
	mDenominator(denom)
{}

Rational::operator double() const
{
	return  double(mNumerator) / mDenominator;
}

Rational::~Rational()
{}