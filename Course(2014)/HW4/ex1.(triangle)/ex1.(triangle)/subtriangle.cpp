#include "subtriangle.h"

SubTraingle::SubTraingle(Point baseOne, Point baseTwo, Point top) :
	Triangle(baseOne, baseTwo, top)
{
	// creating new base side
	int baseLengh = (mBaseTwo.mX - mBaseOne.mX) / 2;
	int height = (mTop.mY - mBaseOne.mY) / 2;
	mBaseOne.mX = mTop.mX - baseLengh/2;
	mBaseOne.mY = mBaseOne.mY + height;
	mBaseTwo.mX = mTop.mX + baseLengh/2;
	mBaseTwo.mY = mBaseTwo.mY + height;
}