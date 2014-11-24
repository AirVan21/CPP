#include "triangle.h"

Triangle::Triangle(Point baseOne, Point baseTwo, Point top) :
	mBaseOne(baseOne),
	mBaseTwo(baseTwo),
	mTop(top)
{
	if (mBaseOne.mY != mBaseTwo.mY) {
		mBaseTwo.mY = mBaseOne.mX;
	}
}

void Triangle::draw()
{
	std::cout << "Base : (" << mBaseOne.mX << ";" << mBaseOne.mY << ") - (" << mBaseTwo.mX << ";" << mBaseTwo.mY << ")\n";
	std::cout << "Side : (" << mBaseOne.mX << ";" << mBaseOne.mY << ") - (" << mTop.mX << ";" << mTop.mY << ")\n";
	std::cout << "Side : (" << mBaseTwo.mX << ";" << mBaseTwo.mY << ") - (" << mTop.mX << ";" << mTop.mY << ")\n";
}
