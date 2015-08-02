#include <stdio.h>
#include <iostream>
#include "uEye.h"
#include "uEyeCameraDriver.h"

using std::cout;
using std::endl;
using std::cin;

int main(int argc, char* argv[])
{
	uEyeCameraDriver *uEyeCameraModel = new uEyeCameraDriver();
	uEyeCameraModel->cameraPreparation();
	char inputParam;
	do
	{
		cout << endl << "Enter: " << endl;
		cout << "  m - to make snapshot" << endl;
		cout << "  s - to save snapshot" << endl;
		cout << "  q - to quit" << endl;
		cout << "  Input = ";
		cin >> inputParam;
		if (inputParam == 'm')
		{
			uEyeCameraModel->makeSnapshotInFreezeCaptureNoWait();
		}
		if (inputParam == 's')
		{
			uEyeCameraModel->storeSnapshots();
		}
		if (inputParam == 'q')
		{
			break;
		}
	} while (inputParam != 'q');
	// Free resourses
	uEyeCameraModel->freeMemoryForFreezeCapture();
	uEyeCameraModel->disableUEyeCameras();
	return 0;
}