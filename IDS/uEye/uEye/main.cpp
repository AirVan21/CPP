#include <stdio.h>
#include <iostream>
#include "uEye.h"
#include "uEyeCameraDriver.h"

using std::cout;
using std::endl;


int main(int argc, char* argv[])
{
	uEyeCameraDriver *uEyeCameraModel = new uEyeCameraDriver();
	uEyeCameraModel->initUEyeCameras();
	uEyeCameraModel->setAutoSensorGainShutter();
	uEyeCameraModel->getImangeForamtParameters();
	uEyeCameraModel->allocMemoryForFreezeCapture();
	uEyeCameraModel->disableUEyeCameras();
	return 0;
}