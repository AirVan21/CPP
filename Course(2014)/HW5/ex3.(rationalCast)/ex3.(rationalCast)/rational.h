// Represents fraction
class Rational
{

public:
	// Constructor
	// @patam numer value for mNumerator
	// @patam numer value for mDenominator
	Rational(int numer, int denom);
	~Rational();

	// Transforms fraction to double
	operator double () const;

private:

	int mNumerator;

	int mDenominator;

};
