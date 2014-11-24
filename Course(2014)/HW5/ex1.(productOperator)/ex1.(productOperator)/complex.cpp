#include "complex.h"

Complex::Complex(int real, int img) :
	mRe(real),
	mImg(img)
{}

Complex operator*(const Complex &multOne, const Complex &multTwo)
{
	return Complex(multOne.mRe * multTwo.mRe - multOne.mImg * multTwo.mImg,
				   multOne.mRe * multTwo.mImg + multTwo.mRe * multOne.mImg);
}

Complex &operator*=(Complex &multOne, const Complex &multTwo)
{
	multOne = operator*(multOne, multTwo);
	return multOne;
}
